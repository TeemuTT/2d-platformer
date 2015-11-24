#ifndef __PSNORMAL__
#define __PSNORMAL__

#include "PlayerState.h"

class PSNormal : public PlayerState
{
public:
    PSNormal(Player *player);
    ~PSNormal();
    virtual PlayerState* update(float &delta);
private:
    void handle_vertical();
    void handle_input();
};

#endif