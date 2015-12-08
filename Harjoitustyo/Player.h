#ifndef __PLAYER__
#define __PLAYER__

#include "SFML\Audio.hpp"

#include "Tile.h"
#include "Entity.h"
#include "PlayerState.h"

class Player : public Entity
{
    // Friend PlayerStates.
    friend class PSDead;
    friend class PSDemo;
    friend class PSNormal;
    friend class PSSprint;
    friend class PSTransition;
public:
    Player(int x, int y, float sizex, float sizey, GameState* gamestate);
    ~Player();

    virtual void update(float &delta);
    virtual void draw(sf::RenderWindow &window);

    void transition();
    void setDemostate();
    void setTiles(std::vector<Tile> tiles);
private:
    PlayerState *state;
    std::vector<Tile> tiles;

    // Sounds should probably be handled by some sort of global manager.
    sf::Sound shootsound;
    sf::SoundBuffer shootbuffer;

    sf::Sound hitsound;
    sf::SoundBuffer hitbuffer;

    sf::Sound sprintsound;
    sf::SoundBuffer sprintbuffer;

    const int SPEED{ 4 };
    const int BULLET_SPEED{ 10 };
    const float GRAVITY{ 0.50F };
    const float JUMP_FORCE{ -10.F };

    bool jumptoggled;
    bool spacetoggled;

    float recoveryclock;
    bool recovering{ false };
};

#endif