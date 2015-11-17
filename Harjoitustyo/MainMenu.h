#ifndef __MAINMENU__
#define __MAINMENU__

#include <string>
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Button.h"

class MainMenu : public GameState
{
public:
    MainMenu(Game *game);
    ~MainMenu();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    int selection{ 0 };
    int options[4] = { 0, 1, 2, 3 };
    sf::Font font;
    sf::Texture texture;
    Button startButton;
    Button optionsButton;
    Button highscoresButton;
    Button quitButton;

    bool escape_toggled{ false };
};

#endif
