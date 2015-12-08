#ifndef __HIGHSCORESSCREEN__
#define __HIGHSCORESSCREEN__

#include <map>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Button.h"
#include "GameState.h"

class HighscoresScreen : public GameState
{
public:
    HighscoresScreen(Game *game);
    ~HighscoresScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
private:
    Button button;
    sf::Font font;
    sf::Text title;
    sf::Text scoretext;
    sf::Texture texture;
    std::map<int, std::string> scores;
};

#endif
