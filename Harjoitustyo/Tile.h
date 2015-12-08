#ifndef __TILE__
#define __TILE__

#include "SFML/Graphics.hpp"

class Tile
{
public:
    Tile(int x, int y);

    sf::RectangleShape getShape();
    int left();
    int top();
    int right();
    int bottom();
private:
    sf::RectangleShape rect;
};

#endif