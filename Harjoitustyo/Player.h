#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerState.h"
#include "Entity.h"
#include "Tile.h"
#include "SFML\Audio.hpp"

class Player : public Entity
{
    friend class PSNormal;
    friend class PSDead;
    friend class PSSprint;
    friend class PSTransition;
    friend class PSDemo;
public:
    Player(int x, int y, float sizex, float sizey, GameState* gamestate);
    ~Player();

    virtual void update(float &delta);
    virtual void draw(sf::RenderWindow &window);

    void transition();
    void setTiles(std::vector<Tile> tiles);
    void setDemostate();
private:
    std::vector<Tile> tiles;
    PlayerState *state;

    // Shouldn't create new buffers in every instance.
    sf::SoundBuffer shootbuffer;
    sf::Sound shootsound;

    sf::SoundBuffer hitbuffer;
    sf::Sound hitsound;

    sf::SoundBuffer sprintbuffer;
    sf::Sound sprintsound;

    const int SPEED = 4;
    const float JUMP_FORCE = -10.F;
    const float GRAVITY = 0.50F;
    const int BULLET_SPEED = 10;

    bool jumptoggled;
    bool spacetoggled;

    bool recovering{ false };
    float recoveryclock;
};

#endif