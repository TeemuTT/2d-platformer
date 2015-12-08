
#include "PSDemo.h"
#include "Player.h"

PSDemo::PSDemo(Player *player) : PlayerState(player)
{

}

PSDemo::~PSDemo()
{

}

PlayerState* PSDemo::update(float &delta)
{
    player->animation.update(*player, 0, 0, AnimationHandler::RUN);
    return nullptr;
}