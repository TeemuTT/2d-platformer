

#include "Entity.h"

#include <iostream>

Entity::Entity(int x, int y, GameState* gamestate)
{
    this->x = x;
    this->y = y;
    this->gamestate = gamestate;
}

Entity::~Entity()
{
    std::cout << "Entity destroyed.\n";
}

int Entity::left()
{
    return rect.getPosition().x;
}

int Entity::top()
{
    return rect.getPosition().y;
}

int Entity::right()
{
    return rect.getPosition().x + rect.getSize().x;
}

int Entity::bottom()
{
    return rect.getPosition().y + rect.getSize().y;
}

sf::Vector2f Entity::getPosition()
{
    return rect.getPosition();
}

sf::Vector2f Entity::getOrigin()
{
    float x = rect.getPosition().x + rect.getSize().x / 2;
    float y = rect.getPosition().y + rect.getSize().y / 2;
    return sf::Vector2f(x, y);
}

bool Entity::isDestroyed()
{
    return destroyed;
}

bool Entity::collision(Entity *entity)
{
    if (getBounds().intersects(entity->getBounds())) {
        return true;
    }
    return false;
}

sf::FloatRect Entity::getBounds()
{
    return rect.getGlobalBounds();
}

void Entity::destroy()
{
    destroyed = true;
}

bool Entity::isGrounded()
{
    return grounded;
}

void Entity::setTexture(sf::Texture* texture)
{
    rect.setTexture(texture);
}

void Entity::setTextureRect(sf::IntRect intrect)
{
    rect.setTextureRect(intrect);
}