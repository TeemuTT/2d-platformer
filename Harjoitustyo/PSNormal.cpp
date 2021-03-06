
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "PSDead.h"
#include "PSNormal.h"
#include "PSSprint.h"
#include "GameScreen.h"

PSNormal::PSNormal(Player *player) : PlayerState(player)
{

}

PSNormal::~PSNormal()
{

}

PlayerState* PSNormal::update(float &delta)
{
    handle_input();

    // Handle PSSprint here. Could make handle_input() return PlayerState*, but it's not worth it currently.
    slide_timer += delta;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && slide_timer >= SLIDE_COOLDOWN) {
        slide_timer = 0;
        player->vy = 0;
        player->grounded = false;
        player->sprintsound.play();
        return new PSSprint(player);
    }

    handle_vertical();
    if (!player->gamestate->getBounds().intersects(player->getBounds())) {
        return new PSDead(player);
    }
    
    for (Entity *e : player->gamestate->getEntities()) {
        if (Enemy *enemy = dynamic_cast<Enemy*>(e)) {
            if (!player->recovering && player->getBounds().intersects(enemy->getBounds())) {
                if (player->hitsound.getStatus() != sf::Sound::Playing) player->hitsound.play();
                player->hit();
                if (player->hitpoints <= 0) {
                    return new PSDead(player);
                }
                player->rect.setFillColor(sf::Color(230, 50, 0));
                player->recovering = true;
                dynamic_cast<GameScreen*>(player->gamestate)->change_score(-140);
            }
        }
    }

    if (player->recovering) {
        player->updateflash(delta);
        player->recoveryclock += delta;
        if (player->recoveryclock >= 1.f) {
            player->recovering = false;
            player->recoveryclock = 0;
        }
    }

    player->rect.setPosition(player->x, player->y);
    player->animation.update(*player, player->vx, player->vy);

    return nullptr;
}

void PSNormal::handle_vertical()
{
    player->vy += player->GRAVITY;

    if (player->vy < 0) {
        int maxpixels = INT_MIN;
        for (Tile t : player->tiles) {
            if (t.top() >= player->bottom()) continue;
            if (t.right() <= player->left()) continue;
            if (t.left() >= player->right()) continue;
            int distance = t.bottom() - player->top();
            if (distance == 0) {
                player->vy = 0;
            }
            if (distance > maxpixels) maxpixels = distance;
        }
        player->y += std::max((int)player->vy, maxpixels);
        return;
    }

    int maxpixels = INT_MAX;
    for (Tile t : player->tiles) {
        if (t.bottom() <= player->top()) continue;
        if (t.right() <= player->left()) continue;
        if (t.left() >= player->right()) continue;
        int distance = t.top() - player->bottom();
        if (distance < maxpixels) maxpixels = distance;
    }
    if (maxpixels == 0) {
        player->vy = 0;
        player->grounded = true;
    }
    else {
        player->grounded = false;
    }
    player->y += std::min((int)player->vy, maxpixels);
}

void PSNormal::handle_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player->vx = -player->SPEED;
        int maxpixels = INT_MIN;
        for (Tile t : player->tiles) {
            if (t.bottom() <= player->top()) continue;
            if (t.top() >= player->bottom()) continue;
            if (t.left() >= player->right()) continue;
            int distance = t.right() - player->left();
            if (distance > maxpixels) maxpixels = distance;
        }
        player->x += std::max((int)player->vx, maxpixels);
        player->rect.setPosition(player->x, player->y);
        player->heading = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player->vx = player->SPEED;
        int maxpixels = INT_MAX;
        for (Tile t : player->tiles) {
            if (t.bottom() <= player->top()) continue;
            if (t.top() >= player->bottom()) continue;
            if (t.right() <= player->left()) continue;
            int distance = t.left() - player->right();
            if (distance < maxpixels) maxpixels = distance;
        }
        player->x += std::min((int)player->vx, maxpixels);
        player->rect.setPosition(player->x, player->y);
        player->heading = 1;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player->vx = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player->vx = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player->grounded && player->jumptoggled) {
        player->grounded = false;
        player->vy = player->JUMP_FORCE;
        player->y += player->vy;
        player->jumptoggled = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player->jumptoggled = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && player->spacetoggled) {
        int bx = player->getOrigin().x + player->heading * player->rect.getSize().x - 4; // magic number: bullet width
        int by = player->getOrigin().y;
        player->gamestate->add_entity(new Bullet(bx, by, sf::Vector2f(player->heading * player->BULLET_SPEED, 0), player->gamestate));
        player->spacetoggled = false;
        player->shootsound.play();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) player->spacetoggled = true;

}