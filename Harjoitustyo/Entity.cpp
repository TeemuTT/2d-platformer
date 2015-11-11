

#include "Entity.h"

#include <iostream>

Entity::~Entity()
{
    std::cout << "Entity destroyed.\n";
}

int Entity::left()
{
    return sprite.getPosition().x;
}

int Entity::top()
{
    return sprite.getPosition().y;
}
int Entity::right()
{
    return sprite.getPosition().x + sprite.getScale().x;
}
int Entity::bottom()
{
    return sprite.getPosition().y + sprite.getScale().y;
}