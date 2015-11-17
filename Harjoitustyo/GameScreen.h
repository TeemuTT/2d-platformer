#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"

class GameScreen : public GameState
{
public:
    GameScreen(Game* game);
    ~GameScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Clock clock;
    float delta;
    int fps;
};

#endif