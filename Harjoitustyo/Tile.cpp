#include "Tile.h"

Tile::Tile(int x, int y)
{
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(16, 16));
}