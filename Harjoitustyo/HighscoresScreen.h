#ifndef __HIGHSCORESSCREEN__
#define __HIGHSCORESSCREEN__


#include <vector>
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Button.h"


class HighscoresScreen : public GameState
{
public:
    HighscoresScreen(Game *game);
    ~HighscoresScreen();

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
