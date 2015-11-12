
#include "Player.h"
#include "Bullet.h"
#include <iostream>

Player::Player(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    //rect.setFillColor(sf::Color::Green);
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(sizex, sizey));
    collidable = true;
    texture.loadFromFile("megaman.png");
    rect.setTexture(&texture);
}

Player::~Player()
{

}

void Player::handleinput()
{
    auto &tiles = gamestate->getTiles(); // ei näin
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        int dx = -SPEED;
        int maxpixels = INT_MIN;
        for (Tile t : tiles) {
            if (t.bottom() <= top()) continue;
            if (t.top() >= bottom()) continue;
            //if (t.right() < left()) continue;
            if (t.left() >= right()) continue;
            int distance = t.right() - left();
            if (distance > maxpixels) maxpixels = distance;            
        }
        x += std::max(dx, maxpixels);
        heading = -1; // tmp for shooting
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        int dx = SPEED;
        int maxpixels = INT_MAX;
        for (Tile t : tiles) {
            if (t.bottom() <= top()) continue;
            if (t.top() >= bottom()) continue;
            if (t.right() <= left()) continue;
            //if (t.left() >= right()) continue;
            int distance = t.left() - right();
            if (distance < maxpixels) maxpixels = distance;
        }
        x += std::min(dx, maxpixels);
        heading = 1; // tmp for shooting
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && grounded && jumptoggled) {
        grounded = false;
        vy = JUMP_FORCE;
        y += vy;
        jumptoggled = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) jumptoggled = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && spacetoggled) {
        int bx = getOrigin().x + heading * rect.getSize().x - 4; // magic number: bullet width
        int by = getOrigin().y;
        gamestate->add_entity(new Bullet(bx, by, sf::Vector2f(heading * BULLET_SPEED, 0), gamestate));
        spacetoggled = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) spacetoggled = true;    
}

void Player::handle_vertical()
{
    auto &tiles = gamestate->getTiles(); // ei näin
    vy += GRAVITY;

    if (vy < 0) {
        int maxpixels = INT_MIN;
        for (Tile t : tiles) {
            //if (t.bottom() <= top()) continue;
            if (t.top() >= bottom()) continue;
            if (t.right() <= left()) continue;
            if (t.left() >= right()) continue;
            int distance = t.bottom() - top();
            if (distance == 0) {
                vy = 0;
            }
            if (distance > maxpixels) maxpixels = distance;
        }
        y += std::max((int)vy, maxpixels);
        return;
    }
    
    int maxpixels = INT_MAX;
    for (Tile t : tiles) {
        if (t.bottom() <= top()) continue;
        //if (t.top() >= bottom()) continue;
        if (t.right() <= left()) continue;
        if (t.left() >= right()) continue;
        int distance = t.top() - bottom();
        if (distance < maxpixels) maxpixels = distance;
    }
    if (maxpixels == 0) {
        vy = 0;
        grounded = true;
    }
    else {
        grounded = false;
    }
    y += std::min((int)vy, maxpixels);
}

void Player::update()
{
    handle_vertical();
    handleinput();
    rect.setPosition(x, y);
}

void Player::draw(sf::RenderWindow &window)
{   
    window.draw(rect);
}