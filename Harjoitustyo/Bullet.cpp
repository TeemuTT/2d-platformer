
#include "Bullet.h"

Bullet::Bullet(int x, int y, sf::Vector2f velocity, GameState* gamestate) : Entity(x, y, gamestate)
{
    this->velocity = velocity;
    rect.setSize(sf::Vector2f(12, 12));

    animation.create_animation(gamestate->get_asset_manager()->getTexture("bullet"), 1, 15, 15, AnimationHandler::IDLE, false);
    animation.update(*this, 0, 0);

    tiles = gamestate->getTiles();
}

Bullet::~Bullet()
{

}

void Bullet::update(float &delta)
{
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
        if (right() < t.left() - 32) continue; // magic number: tile size.
        if (left() > t.right() + 32) continue;
        if (getBounds().intersects(t.getShape().getGlobalBounds())) destroy();
    }
    animation.update(*this, 0, 0);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}