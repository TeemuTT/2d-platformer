
#include <iostream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PSNormal.h"

Player::Player(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(sizex, sizey));
    
    animation.create_animation("run.png", 10, 38, 38, AnimationHandler::RUN, true);
    animation.create_animation("idle.png", 1, 38, 38, AnimationHandler::IDLE, false);
    animation.create_animation("jump.png", 4, 38, 38, AnimationHandler::JUMP, false);
    animation.create_animation("slide.png", 2, 48, 38, AnimationHandler::SPRINT, false);

    shootbuffer.loadFromFile("shoot.wav");
    shootsound.setBuffer(shootbuffer);

    hitbuffer.loadFromFile("playerhit.wav");
    hitsound.setBuffer(hitbuffer);

    sprintbuffer.loadFromFile("slide.wav");
    sprintsound.setBuffer(sprintbuffer);
    
    hitpoints = 3;

    state = new PSNormal(this);
}

Player::~Player()
{
    std::cout << "player destructor\n";
    delete state;
}


void Player::update(float &delta)
{
    PlayerState* state_ = state->update(delta);
    if (state_ != nullptr) {
        delete state;
        state = state_;
    }
}

void Player::draw(sf::RenderWindow &window)
{   
    window.draw(rect);
}

void Player::setTiles(std::vector<Tile> tiles)
{
    this->tiles = tiles;
}

void Player::stop()
{
    vx = 0;
    vy = 0;
    grounded = false;
    delete state;
    state = new PSNormal(this);
}