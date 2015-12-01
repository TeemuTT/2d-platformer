
#include <iostream>

#include "GameScreen.h"
#include "TransitionState.h"
#include "MainMenu.h"
#include "WinState.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

GameScreen::GameScreen(Game* game)
{
    destroyed = false;
    this->game = game;

    level = Level("level_1.txt");
    level.load();
    
    entities.push_back(new Player(0, 0, 50, 64, this));
    dynamic_cast<Player*>(entities.at(0))->setPosition(level.getStart());
    dynamic_cast<Player*>(entities.at(0))->setTiles(level.getTiles());
    
    view = sf::View{ sf::Vector2f(320, 240), sf::Vector2f(640, 480) };

    music.openFromFile("drwily.wav");
    music.setVolume(50);
    music.play();

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
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

bool GameScreen::fadeout()
{
    alpha += 3;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
    if (alpha >= 255) return true;
    return false;
}

GameState* GameScreen::update()
{
    if (cleared) {
        if (fadeout()) return new WinState(game);
        return nullptr;
    }
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                return new MainMenu(game);
            }
        }
    }

    if (music.getStatus() == sf::Music::Stopped) music.play();

    delta = clock.restart().asSeconds();
    fpsclock += delta;
    fps++;
    if (fpsclock >= 1) {
        std::cout << "fps: " << fps << "\n";
        fps = 0;
        fpsclock = 0;
    }
    
    bool isAlive{ false };
    for (Entity *e : entities) {
        e->update(delta);
        if (Player *p = dynamic_cast<Player*>(e)) {
            isAlive = true;
            // Update view to players origin. Keep it inside map bounds.
            view.setCenter(p->getOrigin());
            int max_x = level.getBounds().left + level.getBounds().width;
            int max_y = level.getBounds().top + level.getBounds().height;
            if (view.getCenter().x < WINDOW_WIDTH/2) {
                view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, view.getCenter().y));
            }
            else if (view.getCenter().x > max_x - WINDOW_WIDTH / 2) {
                view.setCenter(sf::Vector2f(max_x - WINDOW_WIDTH/ 2 , view.getCenter().y));
            }
            if (view.getCenter().y < WINDOW_HEIGHT / 2) {
                view.setCenter(sf::Vector2f(view.getCenter().x, WINDOW_HEIGHT / 2));
            }
            else if (view.getCenter().y > max_y - WINDOW_HEIGHT / 2) {
                view.setCenter(sf::Vector2f(view.getCenter().x, max_y - WINDOW_HEIGHT / 2));
            }
            game->set_view(view);
            
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
    if (!isAlive) {
        std::cout << "player is dead\n";
        return new MainMenu(game);
    }

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

    for (Entity *e : queue) {
        entities.push_back(std::move(e));
    }
    queue.clear();

    return nullptr;
}

void GameScreen::draw(sf::RenderWindow &window)
{
    level.getMap()->draw(window);
    for (Entity *e : entities) {
        e->draw(window);
    }
    if (cleared) {
        window.draw(fillRect);
    }
}

void GameScreen::transition()
{
    level.transition();

    for (Entity *e : entities) {
        if (Player *p = dynamic_cast<Player*>(e)) {
            p->setPosition(level.getStart());
            p->setTiles(level.getTiles());

            // Update view to players origin. Keep it inside map bounds.
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

            break;
        }
    }
}