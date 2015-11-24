
#include <iostream>

#include "GameScreen.h"
#include "MainMenu.h"
#include "Player.h"
#include "Enemy.h"

GameScreen::GameScreen(Game* game)
{
    destroyed = false;
    this->game = game;
    entities.push_back(new Player(96, 448, 50, 64, this));
    load_level1();

    view = sf::View{ sf::Vector2f(320, 240), sf::Vector2f(640, 480) };

    map.load("../Debug/map2.tmx", "../Debug/tileset.png", 40, 20);

    entities.push_back(new Enemy(1156, 352, 64, 64, this));
    entities.push_back(new Enemy(608, 64, 64, 64, this));
    entities.push_back(new Enemy(576, 448, 64, 64, this));

    goal.left = 416;
    goal.top = 64;
    goal.height = 64;
    goal.width = 32;

    music.openFromFile("drwily.wav");
    music.setVolume(50);
    music.play();
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

GameState* GameScreen::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                return new MainMenu(game);
            }
            //else if (event.key.code == sf::Keyboard::R) {
            //    load_level2();
            //}
        }
    }

    if (music.getStatus() == sf::Music::Stopped) music.play();

    delta += clock.restart().asSeconds();
    fps++;
    if (delta >= 1) {
        std::cout << "fps: " << fps << "\n";
        fps = 0;
        delta = 0;
    }
    
    for (Entity *e : entities) {
        e->update();
        if (Player *p = dynamic_cast<Player*>(e)) {
            view.setCenter(p->getOrigin());
            game->set_view(view);

            // Ei näin, testausta...
            if (goal.intersects(p->getBounds()) && goal.left == 416) {
                loadlevel2 = true;
            }
            else if (goal.intersects(p->getBounds()) && goal.left == 512) {
                loadlevel1 = true;
            }
        }
    }

    // Karsean näköinen...
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

    if (loadlevel2) {
        load_level2();
    }
    else if (loadlevel1) {
        load_level1();
    }

    return nullptr;
}

void GameScreen::draw(sf::RenderWindow &window)
{    
    map.draw(window);
    for (Entity *e : entities) {
        e->draw(window);
    }
}


// Ei näin, testausta....
void GameScreen::load_level1()
{
    map.load("../Debug/map2.tmx", "../Debug/tileset.png", 40, 20);
    goal.left = 416;
    goal.top = 64;
    
    Player *p = nullptr;
    for (Entity *e : entities) {
        e->update();
        if (p = dynamic_cast<Player*>(e)) {
            p->setPosition(96, 448);
            view.setCenter(p->getOrigin());
            game->set_view(view);
            break;
        }
    }
    entities.clear();
    entities.push_back(p);
    entities.push_back(new Enemy(1156, 352, 64, 64, this));
    entities.push_back(new Enemy(608, 64, 64, 64, this));
    entities.push_back(new Enemy(576, 448, 64, 64, this));
    loadlevel1 = false;
}

void GameScreen::load_level2()
{
    map.load("../Debug/level2.tmx", "../Debug/tileset.png", 40, 20);
    goal.left = 512;
    goal.top = 128;

    Player *p = nullptr;
    for (Entity *e : entities) {
        e->update();
        if (p = dynamic_cast<Player*>(e)) {
            p->setPosition(960, 128);
            view.setCenter(p->getOrigin());
            game->set_view(view);
            break;
        }
    }
    entities.clear();
    entities.push_back(p);
    loadlevel2 = false;
}