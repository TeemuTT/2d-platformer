
#include <iostream>

#include "GameScreen.h"
#include "Player.h"
#include "Enemy.h"

GameScreen::GameScreen(Game* game)
{
    destroyed = false;
    this->game = game;
    map.load(sf::Vector2u(32, 32), 40, 20);
    entities.push_back(new Player(96, 448, 50, 64, this));

    entities.push_back(new Enemy(1156, 352, 32, 64, this));
    entities.push_back(new Enemy(608, 64, 32, 64, this));
    entities.push_back(new Enemy(576, 448, 32, 64, this));

    view = sf::View{ sf::Vector2f(320, 240), sf::Vector2f(640, 480) };
}

GameScreen::~GameScreen()
{
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
        std::cout << "deleted entity.\n";
    }
    std::cout << "GameScreen destroyed\n";
}

void GameScreen::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        destroyed = true;
    }
    for (Entity *e : entities) {
        e->update();
        if (Player *p = dynamic_cast<Player*>(e)) {
            view.setCenter(p->getOrigin());
            game->set_view(view);
        }
    }

    // Erase-remove idiom
    // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    entities.erase( std::remove_if(std::begin(entities), std::end(entities),
                    [](Entity* entity) { return entity->isDestroyed(); }),
                    std::end(entities));

    for (Entity *e : queue) {
        entities.push_back(std::move(e));
    }
    queue.clear();
}

void GameScreen::draw(sf::RenderWindow &window)
{    
    map.draw(window);
    for (Entity *e : entities) {
        e->draw(window);
    }
}


