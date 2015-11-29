#ifndef __PLAYERSTATE__
#define __PLAYERSTATE__

class Player;

class PlayerState
{
public:
    PlayerState(Player* player) { this->player = player; };
    virtual ~PlayerState() {};
    virtual PlayerState* update(float &delta) = 0;
protected:
    Player *player;
};

#endif