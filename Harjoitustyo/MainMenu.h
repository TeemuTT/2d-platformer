#ifndef __MAINMENU__
#define __MAINMENU__

#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "Button.h"
#include "GameState.h"

class MainMenu : public GameState
{
public:
    MainMenu(Game *game);
    ~MainMenu();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Font font;
    sf::Text title;
    sf::Music music;
    sf::Texture texture;
    sf::RectangleShape borders;
    std::vector<Button> buttons;
    int selection{ 0 };
};

#endif
