
#include "Constants.h"
#include "Utilities.h"
#include "PauseState.h"
#include "GameScreen.h"

PauseState::PauseState(Game *game, GameState *previous)
{
    this->game = game;
    this->previous = previous;

    font.loadFromFile("HATTEN.ttf");
    text = centered_text("Paused", previous->getView().getCenter().x, previous->getView().getCenter().y, font);
}

PauseState::~PauseState()
{

}

GameState* PauseState::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
            case sf::Keyboard::P:
                destroyed = true;
                break;

            case sf::Keyboard::Escape:
                dynamic_cast<GameScreen*>(previous)->quitfrompausemenu();
                destroyed = true;
                break;
            }
        }
    }
    return nullptr;
}

void PauseState::draw(sf::RenderWindow &window)
{
    previous->draw(window);
    window.draw(text);
}