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
    bool isClicked(sf::Vector2i point);

private:
    sf::RectangleShape rect;
    sf::Text text;

};

#endif