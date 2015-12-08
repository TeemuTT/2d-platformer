#ifndef __ENEMY__
#define __ENEMY__

#include "SFML/Audio.hpp"

#include "Tile.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(int x, int y, float sizex, float sizey, GameState* gamestate);
    ~Enemy();

    virtual void update(float &delta);
    virtual void draw(sf::RenderWindow &window);

private:
    int start_x, start_y;
    int y_vel{ 1 };
    int x_vel{ 1 };
    
    // Shouldn't create new buffers in every instance.
    sf::SoundBuffer soundBuf;
    sf::Sound hitsound;
};

#endif