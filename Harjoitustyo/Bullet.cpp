
#include "Bullet.h"

Bullet::Bullet(int x, int y, sf::Vector2f velocity, GameState* gamestate) : Entity(x, y, gamestate)
{
    this->velocity = velocity;
    rect.setFillColor(sf::Color::Cyan);
    rect.setSize(sf::Vector2f(8, 8));
    rect.setPosition(sf::Vector2f(x, y));
    tiles = gamestate->getTiles(); // Ehk� ei n�in.
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    // Destroy bullet after some time.
    time += clock.restart().asSeconds();
    if (time > 1.5F) destroy();
    
    // Move.
    x += velocity.x;
    y += velocity.y;
    rect.setPosition(x, y);

    // Destroy when bullet gets out of view.
    sf::View &view = gamestate->getView();
    int viewright = view.getCenter().x + view.getSize().x / 2;
    int viewleft = view.getCenter().x - view.getSize().x / 2;
    if (x < viewleft || x > viewright) destroy();

    // Destroy when bullet hits a tile.
    for (Tile &t : tiles) {
        if (bottom() < t.top()) continue;
        if (top() > t.bottom()) continue;
        if (right() < t.left() - 32) continue;
        if (left() > t.right() + 32) continue;
        if (getBounds().intersects(t.getShape().getGlobalBounds())) destroy();
    }
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}