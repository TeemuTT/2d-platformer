#ifndef __LEVELSELECT__
#define __LEVELSELECT__

#include <vector>

#include "SFML/Audio.hpp"

#include "Button.h"
#include "GameState.h"

class LevelSelect : public GameState
{
public:
    LevelSelect(Game *game);
    ~LevelSelect();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Font font;
    sf::Text text;
    sf::Music music;
    std::vector<Button> buttons;
    int selection{ 1 };
};


#endif