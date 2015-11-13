
#include <iostream>

#include "AnimationHandler.h"

AnimationHandler::AnimationHandler()
{

}

AnimationHandler::~AnimationHandler()
{

}

void AnimationHandler::update(sf::RectangleShape &rect, int heading, int vx, int vy)
{
    timer += clock.restart().asSeconds() * 10;
    if (timer >= 10) timer = 0;
    std::cout << "timer: " << timer << "\n";
    
    Direction dir = RIGHT;
    if (vx > 0) dir = RIGHT;
    else if (vx < 0) dir = LEFT;
    else {
        heading == 1 ? dir = IDLE_RIGHT : dir = IDLE_LEFT;
        timer = 0;
    }
    
    rect.setTexture(animations.at(dir).getTexture());
    rect.setTextureRect(animations.at(dir).getTextureRect((int)timer));
}

void AnimationHandler::create_animation(std::string filename, int images, int w, int h, Direction dir)
{
    Animation animation{ filename, images, w, h };
    animations.emplace(dir, animation);
}
