#ifndef __LEVELSELECT__
#define __LEVELSELECT__

#include "GameState.h"
#include "SFML/Audio.hpp"

class LevelSelect : public GameState
{
public:
    LevelSelect(Game *game);
    ~LevelSelect();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    int selection{ 0 };
    sf::Font font;
    sf::Text text;
    sf::Text text2;
    sf::Music music;
};


#endif