#ifndef __BULLET__
#define __BULLET__

#include "Entity.h"

class Bullet : public Entity
{
public:
    Bullet(int x, int y, sf::Vector2f velocity, GameState* gamestate);
    ~Bullet();

    virtual void update(float &delta);
    virtual void draw(sf::RenderWindow &window);
private:
    sf::Vector2f velocity;
    std::vector<Tile> tiles;
};

#endif