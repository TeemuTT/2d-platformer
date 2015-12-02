
#include "Explosion.h"

Explosion::Explosion(int x, int y, GameState *gamestate) : Entity(x, y, gamestate)
{
    rect.setSize(sf::Vector2f(64, 64));
    rect.setPosition(sf::Vector2f(x, y));

    animation.create_animation("explosion.png", 13, 98, 95, AnimationHandler::IDLE, false);
    animation.update(*this, 0, 0);

    soundBuf.loadFromFile("explosion.wav");
    sound.setBuffer(soundBuf);
    sound.play();
}

Explosion::~Explosion()
{

}

void Explosion::update(float &delta)
{
    timer += delta;
    if (timer >= 1.0) destroyed = true;
    animation.update(*this, 0, 0);
}

void Explosion::draw(sf::RenderWindow &window)
{
    window.draw(rect);
}