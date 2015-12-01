#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"
#include "Level.h"
#include "Player.h"

#include "SFML/Audio.hpp"
#include <string>

class GameScreen : public GameState
{
public:
    GameScreen(Game* game, std::string filename);
    ~GameScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
    virtual void transition();
private:
    sf::Music music;
    sf::Clock clock;
    sf::RectangleShape fillRect;
    int alpha{ 255 };
    float delta;
    float fpsclock;
    int fps;

    bool cleared{ false };
    bool starting{ true };
    bool fadeout();
    bool fadein();
    void center_view(Player *p);
};

#endif