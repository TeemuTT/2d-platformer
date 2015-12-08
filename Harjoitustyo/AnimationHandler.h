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
        RUN, JUMP, IDLE, SPRINT, DEAD
    };

    AnimationHandler();
    ~AnimationHandler();

    void update(Entity &entity, int vx, int vy);
    void update(Entity &entity, int vx, int vy, Direction dir);

    void create_animation(sf::Texture texture, int images, int w, int h, Direction dir, bool looping);
        
private:
    bool has_run{ false };
    bool has_jump{ false };
    bool has_idle{ false };
    bool left{ false };
    sf::Clock clock;

    std::map<Direction, Animation> animations;
};

#endif
