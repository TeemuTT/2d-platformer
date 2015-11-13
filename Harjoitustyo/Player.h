#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.h"
#include "Tile.h"

class Player : public Entity
{
public:
    Player(int x, int y, float sizex, float sizey, GameState* gamestate);
    ~Player();

    virtual void update();
    virtual void draw(sf::RenderWindow &window);
private:
    void handleinput();
    void handle_vertical();

    const int SPEED = 4;
    const float JUMP_FORCE = -10.F;
    const float GRAVITY = 0.50F;
    const int BULLET_SPEED = 10;

    bool jumptoggled;

    // Shoot testing, remove these
    bool spacetoggled;
    int dir = 3;
};

#endif