#ifndef __PAUSESTATE__
#define __PAUSESTATE__

#include "GameState.h"

class PauseState : public GameState
{
public:
    PauseState(Game *game, GameState *previous);
    ~PauseState();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    GameState *previous;
    sf::Font font;
    sf::Text text;
};

#endif