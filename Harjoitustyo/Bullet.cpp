
#include "Bullet.h"

Bullet::Bullet(int x, int y, sf::Vector2f velocity, GameState* gamestate) : Entity(x, y, gamestate)
{
    this->velocity = velocity;
    rect.setFillColor(sf::Color::Cyan);
    rect.setSize(sf::Vector2f(8, 8));
    rect.setPosition(sf::Vector2f(x, y));
    tiles = gamestate->getTiles();
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    time += clock.restart().asSeconds();
    if (time > 1.5F) {
        destroyed = true;
    }
    rect.setPosition(rect.getPosition().x + velocity.x,
                     rect.getPosition().y + velocity.y);

    int cycles = 0;
    for (Tile &t : tiles) {
        if (bottom() < t.top()) continue;
        if (top() > t.bottom()) continue;
        if (right() < t.left() - 32) continue;
        if (left() > t.right() + 32) continue;
        cycles++;
        if (getBounds().intersects(t.getShape().getGlobalBounds())) {
            destroyed = true;
        }
    }
    std::cout << "cycles: " << cycles << "\n";
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}