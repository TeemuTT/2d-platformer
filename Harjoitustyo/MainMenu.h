#ifndef __MAINMENU__
#define __MAINMENU__

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Button.h"
#include "SFML/Audio.hpp"

class MainMenu : public GameState
{
public:
    MainMenu(Game *game);
    ~MainMenu();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    int selection{ 0 };
    std::vector<Button> buttons;
    sf::Font font;
    sf::Text title;
    sf::Texture texture;
    sf::Music music;

    bool escape_toggled{ false };
    bool up_toggled{ false };
    bool down_toggled{ false };
};

#endif
