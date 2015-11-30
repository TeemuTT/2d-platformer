#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"
#include "Level.h"

#include "SFML/Audio.hpp"

class GameScreen : public GameState
{
public:
    GameScreen(Game* game);
    ~GameScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
    virtual void transition();
private:
    sf::Music music;
    sf::Clock clock;
    float delta;
    float fpsclock;
    int fps;
};

#endif