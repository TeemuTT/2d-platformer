
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "PSDemo.h"
#include "PSNormal.h"
#include "PSTransition.h"

Player::Player(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setSize(sf::Vector2f(sizex, sizey));
    
    AssetManager *assets = gamestate->get_asset_manager();
    animation.create_animation(assets->getTexture("player_run"), 8, 567, 556, AnimationHandler::RUN, true);
    animation.create_animation(assets->getTexture("player_idle"), 1, 567, 556, AnimationHandler::IDLE, false);
    animation.create_animation(assets->getTexture("player_jump"), 8, 567, 556, AnimationHandler::JUMP, false);
    animation.create_animation(assets->getTexture("player_sprint"), 9, 567, 556, AnimationHandler::SPRINT, false);
    animation.create_animation(assets->getTexture("player_dead"), 9, 567, 556, AnimationHandler::DEAD, false);
    animation.update(*this, 0, 0, AnimationHandler::IDLE);

    shootsound.setBuffer(assets->getSound("player_shoot"));
    hitsound.setBuffer(assets->getSound("player_hit"));
    sprintsound.setBuffer(assets->getSound("player_sprint"));

    state = new PSNormal(this);
}

Player::~Player()
{
    delete state;
}


void Player::setDemostate()
{
    delete state;
    state = new PSDemo(this);
}

void Player::update(float &delta)
{
    PlayerState* new_state = state->update(delta);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
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

void Player::transition()
{
    delete state;
    state = new PSTransition(this);
}