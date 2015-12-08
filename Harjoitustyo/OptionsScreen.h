#ifndef __OPTIONSSCREEN__
#define __OPTIONSSCREEN__


#include <vector>

#include "SFML/Graphics.hpp"

#include "Button.h"
#include "GameState.h"

class OptionsScreen : public GameState
{
public:
    OptionsScreen(Game *game);
    ~OptionsScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Font font;
    sf::Text title;
    sf::Texture texture;
    std::vector<Button> buttons;
    int selection{ 0 };
};

#endif
