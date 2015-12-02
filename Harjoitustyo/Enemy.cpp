
#include <random>
#include <functional>
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setSize(sf::Vector2f(sizex, sizey));
    rect.setPosition(x, y);
    start_x = x;
    start_y = y;
    hitpoints = 3;

    animation.create_animation("zappy.png", 4, 50, 50, AnimationHandler::IDLE, true);
    animation.update(*this, 0, 0, AnimationHandler::IDLE);

    soundBuf.loadFromFile("hit.wav");
    hitsound.setBuffer(soundBuf);
}

Enemy::~Enemy()
{

}

void Enemy::update(float &delta)
{
    for (Entity* e : gamestate->getEntities()) {
        if (Bullet *b = dynamic_cast<Bullet*>(e)) {
            if (collision(b)) {
                hitsound.play();
                b->destroy();
                hit();
                rect.setFillColor(sf::Color(230, 50, 0));
            }
        }
    }

    if (hitpoints <= 0) destroy();
    updateflash(delta);

    y += y_vel;
    if (std::abs(y - start_y) > 50) y_vel *= -1;

    animation.update(*this, 0, 0);
    rect.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}