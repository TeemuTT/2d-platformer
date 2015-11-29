#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"

#include "SFML/Audio.hpp"

class GameScreen : public GameState
{
public:
    GameScreen(Game* game);
    ~GameScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Music music;
    sf::Clock clock;
    float delta;
    float fpsclock;
    int fps;

    // Ei näin, testausta...
    void load_level1();
    void load_level2();
    bool loadlevel1{ false };
    bool loadlevel2{ false };
};

#endif