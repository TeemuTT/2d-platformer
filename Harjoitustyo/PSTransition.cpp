
#include "PSTransition.h"
#include "Player.h"
#include "PSNormal.h"
#include "AnimationHandler.h"

PSTransition::PSTransition(Player *player) : PlayerState(player)
{

}

PSTransition::~PSTransition()
{

}

PlayerState* PSTransition::update(float &delta)
{
    timer += delta;
    if (timer >= WAIT_TIME) {
        return new PSNormal(player);
    }

    player->animation.update(*player, player->vx, player->vy, AnimationHandler::RUN);

    return nullptr;
}