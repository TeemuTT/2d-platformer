
#include <iostream>

#include "Player.h"
#include "PSDead.h"
#include "Explosion.h"

PSDead::PSDead(Player *player) : PlayerState(player)
{
    player->gamestate->add_entity(new Explosion(player->x, player->y, player->gamestate));
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