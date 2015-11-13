#ifndef __ANIMATIONHANDLER__
#define __ANIMATIONHANDLER__

#include <vector>
#include <string>
#include <map>

#include "SFML\Graphics.hpp"
#include "Animation.h"

class AnimationHandler
{
public:
    enum Direction {
        LEFT, RIGHT, UP, DOWN, IDLE_LEFT, IDLE_RIGHT
    };

    AnimationHandler();
    ~AnimationHandler();

    void update(sf::RectangleShape &rect, int heading, int vx, int vy);

    void create_animation(std::string filename, int images, int w, int h, Direction dir);
        
private:
    float timer;
    sf::Clock clock; // ei ehkä näin

    std::map<Direction, Animation> animations;
};

#endif
