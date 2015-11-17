#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <vector>

#include "Game.h"
#include "Tilemap.h"

class Entity;

class GameState
{
public:
    virtual ~GameState();

    virtual GameState* update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    bool isDestroyed();
    void add_entity(Entity* entity);
    
    std::vector<Entity*> getEntities();
    std::vector<Tile> getTiles();
    sf::View getView();
protected:
    bool destroyed;
    Game* game;
    std::vector<Entity*> entities;
    std::vector<Entity*> queue;
    Tilemap map;
    sf::View view;
};

#endif