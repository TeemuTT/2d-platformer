#ifndef __OPTIONSSCREEN__
#define __OPTIONSSCREEN__


#include <vector>
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Button.h"

class OptionsScreen : public GameState
{
public:
    OptionsScreen(Game *game);
    ~OptionsScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    int selection{ 0 };
    std::vector<Button> buttons;
    sf::Font font;
    sf::Text title;
    sf::Texture texture;
};

#endif
