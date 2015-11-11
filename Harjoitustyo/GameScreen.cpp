
#include "GameScreen.h"
#include "Tilemap.h"

GameScreen::GameScreen(Game* game)
{
    destroyed = false;
    this->game = game;
    Tilemap *map = new Tilemap;
    map->load("../Debug/Image3.png", sf::Vector2u(16, 16), 50, 25);
    entities.push_back(map);

    view = sf::View{ sf::Vector2f(320, 240), sf::Vector2f(240, 240) };
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
    // Testing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.setCenter(sf::Vector2f(view.getCenter().x - 2, view.getCenter().y));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.setCenter(sf::Vector2f(view.getCenter().x + 2, view.getCenter().y));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + 2));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - 2));
    }    
    game->set_view(view);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        destroyed = true;
    }
}

void GameScreen::draw(sf::RenderWindow &window)
{    
    for (Entity *e : entities) {
        e->draw(window);
    }
}