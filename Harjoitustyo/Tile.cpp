#include "Tile.h"

Tile::Tile(int x, int y)
{
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(32, 32));
    rect.setOutlineThickness(0.5);
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Transparent);
}