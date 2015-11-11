#ifndef __ENTITY__
#define __ENTITY__

#include "SFML\Graphics.hpp"

class Entity
{
public:
    virtual ~Entity();

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    int left();
    int top();
    int right();
    int bottom();
private:
    bool destroyed;
    sf::Sprite sprite;
};

#endif