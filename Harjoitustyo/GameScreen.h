#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"

class GameScreen : public GameState
{
public:
    GameScreen(Game* game);
    ~GameScreen();

    virtual void update();
    virtual void draw(sf::RenderWindow &window);    
    
private:
    sf::View view;    
};

#endif