#ifndef __ANIMATIONHANDLER__
#define __ANIMATIONHANDLER__

#include <vector>
#include <string>
#include <map>

#include "SFML\Graphics.hpp"
#include "Animation.h"

class Entity;

class AnimationHandler
{
public:
    enum Direction {
        RUN, JUMP, IDLE
    };

    AnimationHandler();
    ~AnimationHandler();

    void update(Entity &entity, int vx, int vy);

    void create_animation(std::string filename, int images, int w, int h, Direction dir, bool looping);
        
private:
    bool left = false;
    sf::Clock clock; // ei ehkä näin

    std::map<Direction, Animation> animations;
};

#endif
