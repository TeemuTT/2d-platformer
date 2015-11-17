
#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string str, sf::Font &font)
{
    rect.setSize(size);
    rect.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
    rect.setFillColor(sf::Color::Red);
    text.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
    text.setString(str);
    text.setFont(font);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color, std::string str, sf::Font &font)
{
    rect.setSize(size);
    rect.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
    rect.setFillColor(color);
    text.setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
    text.setString(str);
    text.setFont(font);
}

Button::~Button()
{

}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(rect);
    if (focused) text.setColor(sf::Color::Blue);
    else text.setColor(sf::Color::White);
    window.draw(text);
}

void Button::set_focused(bool focused)
{
    this->focused = focused;
}