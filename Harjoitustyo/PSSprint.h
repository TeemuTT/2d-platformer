#ifndef __PSSLIDE__
#define __PSSLIDE__

#include "PlayerState.h"

class PSSprint : public PlayerState
{
public:
    PSSprint(Player *player);
    ~PSSprint();
    virtual PlayerState* update(float &delta);
private:
    void handle_input();

    float timer;
};

#endif