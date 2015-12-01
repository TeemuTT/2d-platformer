#ifndef __TRANSITIONSTATE__
#define __TRANSITIONSTATE__

#include "GameState.h"

class TransitionState : public GameState
{
public:
    TransitionState(Game* game, GameState* previous);
    ~TransitionState();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);

    void setPrevious(GameState *state);
private:
    GameState *previous;
    sf::Clock clock;
    sf::RectangleShape fillRect;
    int alpha{ 0 };
    float delta;
    float timer;
    bool post{ false };
    float TRANSITION_TIME{ 2 };
};

#endif