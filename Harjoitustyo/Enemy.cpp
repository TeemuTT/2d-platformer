
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "GameScreen.h"

Enemy::Enemy(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setSize(sf::Vector2f(sizex, sizey));
    start_x = x;
    start_y = y;

    animation.create_animation(gamestate->get_asset_manager()->getTexture("zappy"), 4, 50, 50, AnimationHandler::IDLE, true);
    animation.update(*this, 0, 0, AnimationHandler::IDLE);

    hitsound.setBuffer(gamestate->get_asset_manager()->getSound("enemy_hit"));
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

    if (hitpoints <= 0) {
        dynamic_cast<GameScreen*>(gamestate)->change_score(110);
        gamestate->add_entity(new Explosion(x, y, gamestate));
        destroy();
    }
    updateflash(delta);

    y += y_vel;
    if (std::abs(y - start_y) > 50) y_vel *= -1;

    x += x_vel;
    if (std::abs(x - start_x) > 10) x_vel *= -1;

    rect.setPosition(x, y);
    animation.update(*this, 0, 0);
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}