#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setSize(sf::Vector2f(sizex, sizey));
    rect.setPosition(x, y);

    texture.loadFromFile("drill.png");
    rect.setTexture(&texture);
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
    for (Entity* e : gamestate->getEntities()) {
        if (Bullet *b = dynamic_cast<Bullet*>(e)) {
            if (collision(b)) {
                destroyed = true;
                b->destroy();
            }
        }
    }
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}