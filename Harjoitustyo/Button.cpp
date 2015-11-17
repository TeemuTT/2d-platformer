
#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string str, sf::Font &font)
{
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(sf::Color::Red);
    text.setPosition(pos);
    text.setString(str);
    text.setFont(font);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color, std::string str, sf::Font &font)
{
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(color);
    text.setPosition(pos);
    text.setString(str);
    text.setFont(font);
}

Button::~Button()
{

}

bool Button::isClicked(sf::Vector2i point)
{
    return rect.getGlobalBounds().contains(point.x, point.y);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(rect);
    window.draw(text);
}