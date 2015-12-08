#include "Tile.h"

Tile::Tile(int x, int y)
{
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(32, 32));
    rect.setOutlineThickness(0.5);
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Transparent);
}

sf::RectangleShape Tile::getShape()
{
    return rect;
}

int Tile::left()
{
    return rect.getPosition().x;
}

int Tile::top()
{
    return rect.getPosition().y;
}

int Tile::right()
{
    return rect.getPosition().x + rect.getSize().x;
}

int Tile::bottom()
{
    return rect.getPosition().y + rect.getSize().y;
}