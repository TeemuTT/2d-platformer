
#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string str, sf::Font &font)
{
    text.setFont(font);
    text.setString(str);
    text.setPosition(pos.x - text.getGlobalBounds().width / 2, pos.y);
    rect.setSize(size);
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(text.getPosition());
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color, std::string str, sf::Font &font)
{
    text.setFont(font);
    text.setString(str);
    text.setPosition(pos.x - text.getGlobalBounds().width / 2, pos.y);
    rect.setSize(size);
    rect.setFillColor(color);
    rect.setPosition(text.getPosition());
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