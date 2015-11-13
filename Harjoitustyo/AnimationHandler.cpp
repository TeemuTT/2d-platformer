
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
    
    // Should have at least idle tex/anim. This turns out as white box.
    if (!has_idle) {
        return;
    }

    Direction dir = IDLE;
    if (has_run) {
        if (vx > 0) {
            left = false;
            dir = RUN;
        }
        else if (vx < 0) {
            left = true;
            dir = RUN;
        }
    }
    if (has_jump) {
        if (!entity.isGrounded()) {
            dir = JUMP;
        }
        else {
            animations.at(JUMP).reset();
        }
    }
    
    entity.setTexture(animations.at(dir).getTexture());
    entity.setTextureRect(animations.at(dir).getTextureRect(delta, left));
}

void AnimationHandler::create_animation(std::string filename, int images, int w, int h, Direction dir, bool looping)
{
    Animation animation{ filename, images, w, h, looping };
    animations.emplace(dir, animation);
    switch (dir) {
    case RUN:
        has_run = true;
        break;
    case JUMP:
        has_jump = true;
        break;
    case IDLE:
        has_idle = true;
        break;
    }
}
