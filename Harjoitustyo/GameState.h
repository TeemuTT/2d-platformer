#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <vector>

#include "Game.h"
#include "Level.h"
#include "Tilemap.h"
#include "AssetManager.h"

class Entity;

class GameState
{
public:
    virtual ~GameState();

    virtual GameState* update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void transition();

    bool isDestroyed();
    void add_entity(Entity* entity);
    
    sf::View getView();
    sf::FloatRect getBounds();
    std::vector<Tile> getTiles();
    std::vector<Entity*> getEntities();
    AssetManager* get_asset_manager();

protected:
    Game* game;
    Level level;
    sf::View view;
    bool destroyed;
    std::vector<Entity*> queue;
    std::vector<Entity*> entities;
};

#endif