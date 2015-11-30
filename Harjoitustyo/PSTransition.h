#ifndef __PSTRANSITION__
#define __PSTRANSITION__

#include "PlayerState.h"

class PSTransition : public PlayerState
{
public:
    PSTransition(Player *player);
    ~PSTransition();
    virtual PlayerState* update(float &delta);
private:
    float timer;
    const float WAIT_TIME{ 2.0 };
};

#endif