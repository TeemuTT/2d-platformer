#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "SFML/Graphics.hpp"

class Rectangle
{
public:
    sf::RectangleShape rect;

    Rectangle();
    sf::RectangleShape getShape();
    int left();
    int top();
    int right();
    int bottom();
};

#endif