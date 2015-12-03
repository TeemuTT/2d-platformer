#ifndef __LEVELSELECT__
#define __LEVELSELECT__

#include "Button.h"
#include "GameState.h"
#include "SFML/Audio.hpp"
#include <vector>

class LevelSelect : public GameState
{
public:
    LevelSelect(Game *game);
    ~LevelSelect();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    int selection{ 1 };
    std::vector<Button> buttons;
    sf::Font font;
    sf::Text text;
    sf::Music music;
};


#endif