#ifndef __PSDEAD__
#define __PSDEAD__

#include "PlayerState.h"


class PSDead : public PlayerState
{
public:
    PSDead(Player* player);
    ~PSDead();
    virtual PlayerState* update(float &delta);
private:
    float waittime;
};

#endif