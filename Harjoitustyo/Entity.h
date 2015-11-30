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

    virtual void update(float &delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin();

    bool isDestroyed();
    bool isGrounded();
    void setPosition(int x, int y);
    void setPosition(sf::FloatRect pos);
    void setTexture(sf::Texture* texture);
    void setTextureRect(sf::IntRect intrect);
    bool collision(Entity *entity);
    void destroy();
    void hit();
    void updateflash(float &delta);
    sf::FloatRect getBounds();

protected:
    sf::Texture texture;
    sf::RectangleShape rect;

    GameState* gamestate;
    AnimationHandler animation;

    int x, y;
    float vx, vy;
    float flashclock;
    int heading{ 1 };
    int hitpoints{ 0 };
    bool grounded{ true };
    bool destroyed{ false };

    int top();
    int left();
    int right();
    int bottom();

};

#endif