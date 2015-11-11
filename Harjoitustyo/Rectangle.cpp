#include "Rectangle.h"

Rectangle::Rectangle()
{

}

sf::RectangleShape Rectangle::getShape()
{
    return rect;
}

int Rectangle::left()
{
    return rect.getPosition().x;
}

int Rectangle::top()
{
    return rect.getPosition().y;
}

int Rectangle::right()
{
    return rect.getPosition().x + rect.getSize().x;
}

int Rectangle::bottom()
{
    return rect.getPosition().y + rect.getSize().y;
}