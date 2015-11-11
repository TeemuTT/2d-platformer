#ifndef __GAMESTATE__
#define __GAMESTATE__

#include "Game.h"
#include <iostream>

class GameState
{
public:
    virtual ~GameState() {};

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    bool isDestroyed() { return destroyed; }
protected:
    bool destroyed;
    Game* game;
};

#endif