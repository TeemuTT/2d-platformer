
#include "Utilities.h"

sf::Text centered_text(std::string str, int x, int y, sf::Font &font)
{
    sf::Text text(str, font);
    text.setColor(sf::Color::White);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
    text.setPosition(sf::Vector2f(x, y));
    return text;
}