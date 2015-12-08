#ifndef __WINSTATE__
#define __WINSTATE__

#include "SFML/Audio.hpp"

#include "GameState.h"

class WinState : public GameState
{
public:
    WinState(Game* game, bool win, int score);
    ~WinState();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Music music;
    
    sf::Font font;
    sf::Text label;
    sf::Text prompt;
    sf::Text nametext;
    sf::Text scoretext;
    sf::Text nameprompt;
    
    sf::RectangleShape fillRect;
    sf::Clock clock;
    
    bool win{ true };
    float delta, timer;
    int alpha{ 255 }, score;
    std::string name;
};

#endif