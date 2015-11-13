#ifndef __ENEMY__
#define __ENEMY__

#include "Entity.h"
#include "Tile.h"

#include <vector>

class Enemy : public Entity
{
public:
    Enemy(int x, int y, float sizex, float sizey, GameState* gamestate);
    ~Enemy();

    virtual void update();
    virtual void draw(sf::RenderWindow &window);
};

#endif