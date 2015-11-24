
#include <iostream>

#include "Player.h"
#include "PSDead.h"

PSDead::PSDead(Player *player) : PlayerState(player)
{

}

PSDead::~PSDead()
{
    std::cout << "PSDead stop\n";
}

PlayerState* PSDead::update(float &delta)
{
    waittime += delta;
    if (waittime >= 2) {
        player->destroy();
    }
    return nullptr;
}