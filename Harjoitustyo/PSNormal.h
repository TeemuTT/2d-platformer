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

    float slide_timer{ 1.0 };
    const float SLIDE_COOLDOWN{ 1.0 };
};

#endif