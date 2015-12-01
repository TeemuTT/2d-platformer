
#include "WinState.h"
#include "MainMenu.h"
#include "Constants.h"

WinState::WinState(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    label.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 40));
    label.setFont(font);
    label.setString("Level cleared!");
    label.setColor(sf::Color::White);

    prompt.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 150));
    prompt.setFont(font);
    prompt.setString("Press Enter to continue.");
    prompt.setColor(sf::Color::White);

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
}

WinState::~WinState()
{

}

GameState* WinState::update()
{
    alpha -= 3;
    if (alpha <= 0) alpha = 0;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));

    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Return) {
                return new MainMenu(game);
            }
        }
    }

    return nullptr;
}

void WinState::draw(sf::RenderWindow &window)
{
    window.draw(label);
    window.draw(prompt);
    window.draw(fillRect);
}

void WinState::transition()
{

}