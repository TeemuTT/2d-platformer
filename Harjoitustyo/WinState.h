#ifndef __WINSTATE__
#define __WINSTATE__

#include "GameState.h"
#include "SFML/Audio.hpp"

class WinState : public GameState
{
public:
    WinState(Game* game, bool win, int score);
    ~WinState();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
    virtual void transition();
private:
    sf::Music music;
    sf::Font font;
    sf::Text label;
    sf::Text scoretext;
    sf::Text prompt;
    sf::RectangleShape fillRect;
    sf::Clock clock;
    float delta, timer;
    int alpha{ 255 };
    bool win{ true };
};

#endif