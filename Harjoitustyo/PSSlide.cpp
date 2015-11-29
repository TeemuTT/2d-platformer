
#include "PSSlide.h"
#include "PSNormal.h"
#include "PSDead.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AnimationHandler.h"

PSSlide::PSSlide(Player *player) : PlayerState(player)
{
    player->vx = player->SPEED * 2 * player->heading;
}

PSSlide::~PSSlide()
{

}

PlayerState* PSSlide::update(float &delta)
{
    timer += delta;
    if (timer >= 0.33) return new PSNormal(player);

    handle_input();

    auto &tiles = player->gamestate->getTiles(); // ei näin
    if (player->vx < 0) {
        int maxpixels = INT_MIN;
        for (Tile t : tiles) {
            if (t.bottom() <= player->top()) continue;
            if (t.top() >= player->bottom()) continue;
            if (t.left() >= player->right()) continue;
            int distance = t.right() - player->left();
            if (distance > maxpixels) maxpixels = distance;
        }
        player->x += std::max((int)player->vx, maxpixels);
    }
    else {
        int maxpixels = INT_MAX;
        for (Tile t : tiles) {
            if (t.bottom() <= player->top()) continue;
            if (t.top() >= player->bottom()) continue;
            if (t.right() <= player->left()) continue;
            int distance = t.left() - player->right();
            if (distance < maxpixels) maxpixels = distance;
        }
        player->x += std::min((int)player->vx, maxpixels);
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
    player->animation.update(*player, player->vx, player->vy, AnimationHandler::SPRINT);

    return nullptr;
}

void PSSlide::handle_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && player->spacetoggled) {
        int bx = player->getOrigin().x + player->heading * player->rect.getSize().x - 4; // magic number: bullet width
        int by = player->getOrigin().y;
        player->gamestate->add_entity(new Bullet(bx, by, sf::Vector2f(player->heading * player->BULLET_SPEED, 0), player->gamestate));
        player->spacetoggled = false;
        player->shootsound.play();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) player->spacetoggled = true;
}