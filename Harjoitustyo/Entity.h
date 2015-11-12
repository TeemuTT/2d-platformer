#ifndef __ENTITY__
#define __ENTITY__

#include "SFML\Graphics.hpp"
#include "GameState.h"

class Entity
{
public:
    Entity(int x, int y, GameState* gamestate);
    virtual ~Entity();

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin();

    bool isDestroyed();
    bool isCollidable();
    bool collision(Entity *entity);
    void destroy();
    sf::FloatRect getBounds();

protected:
    bool destroyed;
    sf::Texture texture;
    sf::RectangleShape rect;

    GameState* gamestate;

    int x, y;
    float vy;
    bool grounded;
    bool collidable;
    int heading = 1;

    int left();
    int top();
    int right();
    int bottom();

    
};

#endif