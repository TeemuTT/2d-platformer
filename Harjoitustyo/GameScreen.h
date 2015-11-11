#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"

class GameScreen : public GameState
{
public:
    GameScreen();
    ~GameScreen();

    virtual void update();
    virtual void draw(sf::RenderWindow &window);
};

#endif