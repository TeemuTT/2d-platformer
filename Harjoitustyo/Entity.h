#ifndef __ENTITY__
#define __ENTITY__

#include "SFML\Graphics.hpp"
#include "GameState.h"
#include "AnimationHandler.h"

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
    bool isGrounded();
    void setTexture(sf::Texture* texture);
    void setTextureRect(sf::IntRect intrect);
    bool collision(Entity *entity);
    void destroy();
    sf::FloatRect getBounds();

protected:
    bool destroyed;
    sf::Texture texture;
    sf::RectangleShape rect;

    GameState* gamestate;
    AnimationHandler animation;

    int x, y;
    float vx, vy;
    bool grounded;
    bool collidable;
    int heading = 1;

    int left();
    int top();
    int right();
    int bottom();

    
};

#endif