#ifndef __GAMESTATE__
#define __GAMESTATE__

#include "Game.h"
#include <iostream>
#include <vector>
#include "Tilemap.h"

class Entity;

class GameState
{
public:
    virtual ~GameState() {};

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    bool isDestroyed() { return destroyed; }
    void add_entity(Entity* entity);
    std::vector<Entity*> getEntities();
    std::vector<Tile> getTiles();
protected:
    bool destroyed;
    Game* game;
    std::vector<Entity*> entities;
    std::vector<Entity*> queue;
    Tilemap map;
};

#endif