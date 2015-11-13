
#include "AnimationHandler.h"
#include "Entity.h"

AnimationHandler::AnimationHandler()
{

}

AnimationHandler::~AnimationHandler()
{

}

void AnimationHandler::update(Entity &entity, int vx, int vy)
{
    float delta = clock.restart().asSeconds() * 10;
    
    Direction dir = IDLE;
    if (vx > 0) {
        left = false;
        dir = RUN;
    }
    else if (vx < 0) {
        left = true;
        dir = RUN;
    }
    else {
        dir = IDLE;
    }
    if (!entity.isGrounded()) {
        dir = JUMP;
    }
    else {
        animations.at(JUMP).reset();
    }
    
    entity.setTexture(animations.at(dir).getTexture());
    entity.setTextureRect(animations.at(dir).getTextureRect(delta, left));
}

void AnimationHandler::create_animation(std::string filename, int images, int w, int h, Direction dir, bool looping)
{
    Animation animation{ filename, images, w, h, looping };
    animations.emplace(dir, animation);
}
