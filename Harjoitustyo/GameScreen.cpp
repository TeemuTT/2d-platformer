
#include <iostream>

#include "GameScreen.h"
#include "TransitionState.h"
#include "MainMenu.h"
#include "WinState.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "PauseState.h"

GameScreen::GameScreen(Game* game, std::string filename)
{
    this->game = game;
    this->score = 10;

    level = Level(filename);
    level.load();
    std::vector<std::pair<int, int>> positions = level.getEnemyPositions();
    for (auto pos : positions) {
        entities.push_back(new Enemy(pos.first, pos.second, 64.f, 64.f, this));
    }

    Player *player = new Player(0, 0, 50, 64, this);
    player->setPosition(level.getStart());
    player->setTiles(level.getTiles());
    entities.push_back(player);

    view.setSize(640, 480);
    center_view(player);
    game->set_view(view);

    music.openFromFile("drwily.wav");
    music.setVolume(33);
    music.play();

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));

    font.loadFromFile("HATTEN.ttf");
    scoretext.setString("Score: " + std::to_string(score));
    scoretext.setFont(font);
    scoretext.setColor(sf::Color::White);
    scoretext.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 200));
}

void GameScreen::center_view(Player *p)
{
    view.setCenter(p->getOrigin());
    int max_x = level.getBounds().left + level.getBounds().width;
    int max_y = level.getBounds().top + level.getBounds().height;
    if (view.getCenter().x < WINDOW_WIDTH / 2) {
        view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, view.getCenter().y));
    }
    else if (view.getCenter().x > max_x - WINDOW_WIDTH / 2) {
        view.setCenter(sf::Vector2f(max_x - WINDOW_WIDTH / 2, view.getCenter().y));
    }
    if (view.getCenter().y < WINDOW_HEIGHT / 2) {
        view.setCenter(sf::Vector2f(view.getCenter().x, WINDOW_HEIGHT / 2));
    }
    else if (view.getCenter().y > max_y - WINDOW_HEIGHT / 2) {
        view.setCenter(sf::Vector2f(view.getCenter().x, max_y - WINDOW_HEIGHT / 2));
    }
    game->set_view(view);
}

GameScreen::~GameScreen()
{
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
        //std::cout << "deleted entity.\n";
    }
    std::cout << "GameScreen destroyed\n";
}

/*
Screen fade effect.
*/
bool GameScreen::fade(bool fadein)
{
    fadein ? alpha -= 3 : alpha += 3;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
    if (alpha <= 0) return true;
    
    if (fadein) {
        if (alpha <= 0) return true;
    }
    else if (alpha >= 255) return true;

    return false;
}

GameState* GameScreen::update()
{
    if (starting) {
        if (fade(true)) starting = false;
        return nullptr;
    }
    else if (cleared) {
        if (fade(false)) return new WinState(game, true, score);
        return nullptr;
    }
    else if (!alive) {
        if (fade(false)) return new WinState(game, false, score);
        return nullptr;
    }
    else if (abort) {
        return new MainMenu(game);
    }

    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                game->push_state(new PauseState(game, this));
            }
        }
    }

    if (music.getStatus() == sf::Music::Stopped) music.play();

    delta = clock.restart().asSeconds();
    timer += delta;
    if (timer >= 1) {
        score--;
        timer = 0;
    }
    
    alive = false;
    for (Entity *e : entities) {
        e->update(delta);
        if (Player *p = dynamic_cast<Player*>(e)) {
            alive = true;
            center_view(p);            
            // Are we at the end of the current tilemap? Load next one if it exists. Else quit.
            if (level.getGoal().intersects(p->getBounds())) {
                if (level.hasNext()) {
                    p->transition();
                    game->push_state(new TransitionState(game, this));
                }
                else {
                    p->transition();
                    cleared = true;
                }
            }
        }
    }

    // Remove destroyed entities.
    // Erase-remove idiom
    // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    entities.erase( std::remove_if(std::begin(entities), std::end(entities),
                    [](Entity *entity) {
                        if (entity->isDestroyed()) {
                            delete entity;
                            return true;
                        }
                        return false;
                    }),
                    std::end(entities));

    // Add new entities from queue.
    for (Entity *e : queue) {
        entities.push_back(std::move(e));
    }
    queue.clear();

    scoretext.setString("Score: " + std::to_string(score));
    scoretext.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 230));

    return nullptr;
}

void GameScreen::draw(sf::RenderWindow &window)
{
    level.getMap()->draw(window);
    for (Entity *e : entities) {
        e->draw(window);
    }
    if (cleared || starting || !alive) {
        window.draw(fillRect);
    }
    window.draw(scoretext);
}

/*
Transition to the next tilemap. Clear entities and spawn new ones.
*/
void GameScreen::transition()
{
    level.transition();

    Player *player = nullptr;
    for (Entity *e : entities) {
        if (player = dynamic_cast<Player*>(e)) {
            player->setPosition(level.getStart());
            player->setTiles(level.getTiles());
            center_view(player);
            break;
        }
    }
    entities.clear();
    entities.push_back(player);

    std::vector<std::pair<int, int>> positions = level.getEnemyPositions();
    for (auto pos : positions) {
        entities.push_back(new Enemy(pos.first, pos.second, 64.f, 64.f, this));
    }
}

void GameScreen::quitfrompausemenu()
{
    abort = true;
}

void GameScreen::change_score(int change)
{
    score += change;
}