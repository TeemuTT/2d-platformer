
#include "Enemy.h"
#include "Player.h"
#include "MainMenu.h"
#include "WinState.h"
#include "Utilities.h"
#include "Constants.h"
#include "PauseState.h"
#include "GameScreen.h"
#include "TransitionState.h"

GameScreen::GameScreen(Game* game, std::string filename)
{
    this->game = game;
    this->score = 100;

    std::uniform_int_distribution<int> dist(0, 2);

    level = Level(filename);
    level.load();
    auto positions = level.getEnemyPositions();
    for (auto pos : positions)
        entities.push_back(new Enemy(pos.first, pos.second, 64, 64, dist(gen), this));

    Player *player = new Player(0, 0, 50, 64, this);
    player->setPosition(level.getStart());
    player->setTiles(level.getTiles());
    entities.push_back(player);

    view.setSize(640, 480);
    center_view(player);
    game->set_view(view);

    music.openFromFile("sounds/Orbital_Colossus.ogg");
    music.setVolume(33);
    music.play();

    // fillRect is used for screen fading.
    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));

    font.loadFromFile("HATTEN.ttf");
    scoretext = centered_text("Score: " + std::to_string(score), view.getCenter().x, view.getCenter().y - WINDOW_HEIGHT / 2, font);
}

GameScreen::~GameScreen()
{
    music.stop();
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
    }
}

// Screen fade effect.
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
    switch (status) {
    case START:
        if (fade(true)) status = NORMAL;
        return nullptr;
    case END:
        if (fade(false)) return new WinState(game, alive, score);
        return nullptr;
    case QUIT:
        return new MainMenu(game);
    }

    if (music.getStatus() == sf::Music::Stopped) music.play();
    delta = clock.restart().asSeconds();

    // Decrement score every second.
    timer += delta;
    if (timer >= 1) {
        score--;
        timer = 0;
    }

    sf::Event event;
    while (game->get_window().pollEvent(event))
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            game->push_state(new PauseState(game, this));

    status = END;
    alive = false;
    for (Entity *e : entities) {
        e->update(delta);
        if (Player *p = dynamic_cast<Player*>(e)) {
            status = NORMAL;
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
                    status = END;
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
    for (Entity *e : queue) entities.push_back(std::move(e));
    queue.clear();

    scoretext.setString("Score: " + std::to_string(score));
    scoretext.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - WINDOW_HEIGHT / 2));

    return nullptr;
}

void GameScreen::draw(sf::RenderWindow &window)
{
    level.getMap()->draw(window);
    for (Entity *e : entities)  e->draw(window);
    if (status != NORMAL) window.draw(fillRect);
    window.draw(scoretext);
}


// Transition to the next tilemap. Clear entities and spawn new ones.
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

    std::uniform_int_distribution<int> dist(0, 2);
    std::vector<std::pair<int, int>> positions = level.getEnemyPositions();
    for (auto pos : positions) {
        entities.push_back(new Enemy(pos.first, pos.second, 64.f, 64.f, dist(gen), this));
    }
}

void GameScreen::quitfrompausemenu()
{
    status = QUIT;
}

void GameScreen::change_score(int change)
{
    score += change;
}

// Centers the view on the player's origin.
void GameScreen::center_view(Player *p)
{
    view.setCenter(p->getOrigin());
    int max_x = level.getBounds().left + level.getBounds().width;
    int max_y = level.getBounds().top + level.getBounds().height;
    int view_x = view.getCenter().x, view_y = view.getCenter().y;

    if (view_x < WINDOW_WIDTH / 2)
        view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, view.getCenter().y));
    else if (view_x > max_x - WINDOW_WIDTH / 2)
        view.setCenter(sf::Vector2f(max_x - WINDOW_WIDTH / 2, view.getCenter().y));

    if (view_y < WINDOW_HEIGHT / 2)
        view.setCenter(sf::Vector2f(view.getCenter().x, WINDOW_HEIGHT / 2));
    else if (view_y > max_y - WINDOW_HEIGHT / 2)
        view.setCenter(sf::Vector2f(view.getCenter().x, max_y - WINDOW_HEIGHT / 2));

    game->set_view(view);
}
