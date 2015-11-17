#ifndef __BUTTON__
#define __BUTTON__

#include <string>

#include "SFML/Graphics.hpp"

class Button
{
public:
    Button();
    Button(sf::Vector2f pos, sf::Vector2f size, std::string str, sf::Font &font);
    Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color, std::string str, sf::Font &font);
    ~Button();

    void draw(sf::RenderWindow &window);
    void set_focused(bool focused);

private:
    sf::RectangleShape rect;
    sf::Text text;
    bool focused{ false };
};

#endif