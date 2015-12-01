
#include "TransitionState.h"
#include "Constants.h"

#include <iostream>

TransitionState::TransitionState(Game *game, GameState *previous)
{
    destroyed = false;
    this->game = game;
    this->previous = previous;

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
}

TransitionState::~TransitionState()
{

}

GameState* TransitionState::update()
{
    delta = clock.restart().asSeconds();
    timer += delta;
    if (timer >= 1) {
        if (!post) {
            previous->transition();
            post = true;
        }
        alpha -= 4;
    }
    else alpha += 4;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
    if (timer >= 2) destroyed = true;
    return nullptr;
}

void TransitionState::draw(sf::RenderWindow &window)
{
    previous->draw(window);
    window.draw(fillRect);
}

void TransitionState::setPrevious(GameState *previous)
{
    this->previous = previous;
}