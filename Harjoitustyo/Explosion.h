#ifndef __EXPLOSION__
#define __EXPLOSION__

#include "SFML/Audio.hpp"

#include "Entity.h"

class Explosion : public Entity
{
public:
    Explosion(int x, int y, GameState *gamestate);
    ~Explosion();

    virtual void update(float &delta);
    virtual void draw(sf::RenderWindow &window);
private:
    float timer;

    // Shouldn't create new buffers in every instance.
    sf::SoundBuffer soundBuf;
    sf::Sound sound;
};

#endif