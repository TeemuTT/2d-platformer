
#include "Player.h"
#include "Bullet.h"

Player::Player(int x, int y, float sizex, float sizey, GameState* gamestate) : Entity(x, y, gamestate)
{
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(sizex, sizey));
    
    animation.create_animation("run.png", 10, 38, 38, AnimationHandler::RUN, true);
    animation.create_animation("idle.png", 1, 38, 38, AnimationHandler::IDLE, false);
    animation.create_animation("jump.png", 4, 38, 38, AnimationHandler::JUMP, false);

    shootbuffer.loadFromFile("shoot.wav");
    shoot.setBuffer(shootbuffer);
}

Player::~Player()
{

}

void Player::handleinput()
{
    auto &tiles = gamestate->getTiles(); // ei näin
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        vx = -SPEED;
        int maxpixels = INT_MIN;
        for (Tile t : tiles) {
            if (t.bottom() <= top()) continue;
            if (t.top() >= bottom()) continue;
            if (t.left() >= right()) continue;
            int distance = t.right() - left();
            if (distance > maxpixels) maxpixels = distance;
        }
        x += std::max((int)vx, maxpixels);
        heading = -1; // tmp for shooting
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        vx = SPEED;
        int maxpixels = INT_MAX;
        for (Tile t : tiles) {
            if (t.bottom() <= top()) continue;
            if (t.top() >= bottom()) continue;
            if (t.right() <= left()) continue;
            int distance = t.left() - right();
            if (distance < maxpixels) maxpixels = distance;
        }
        x += std::min((int)vx, maxpixels);
        heading = 1; // tmp for shooting
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) vx = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) vx = 0;

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
        shoot.play();
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

void Player::update(float &delta)
{
    handle_vertical();
    handleinput();
    rect.setPosition(x, y);
    animation.update(*this, vx, vy);
}

void Player::draw(sf::RenderWindow &window)
{   
    window.draw(rect);
}