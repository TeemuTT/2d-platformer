#ifndef __PSDEMO__
#define __PSDEMO__

#include "PlayerState.h"

class PSDemo : public PlayerState
{
public:
    PSDemo(Player *player);
    ~PSDemo();
    virtual PlayerState* update(float &delta);
};


#endif