
#include "PauseState.h"
#include "Constants.h"
#include "GameScreen.h"

PauseState::PauseState(Game *game, GameState *previous)
{
    this->game = game;
    this->previous = previous;

    font.loadFromFile("HATTEN.ttf");
    text.setFont(font);
    text.setString("Paused");
    text.setPosition(previous->getView().getCenter());
    text.setColor(sf::Color::White);
}

PauseState::~PauseState()
{

}

GameState* PauseState::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                destroyed = true;
            }
            else if (event.key.code == sf::Keyboard::Escape) {
                dynamic_cast<GameScreen*>(previous)->quitfrompausemenu();
                destroyed = true;
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