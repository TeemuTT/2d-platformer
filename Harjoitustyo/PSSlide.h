#ifndef __PSSLIDE__
#define __PSSLIDE__

#include "PlayerState.h"

class PSSlide : public PlayerState
{
public:
    PSSlide(Player *player);
    ~PSSlide();
    virtual PlayerState* update(float &delta);
private:
    void handle_input();

    float timer;
};

#endif