
#include <iostream>

#include "OptionsScreen.h"
#include "Constants.h"

OptionsScreen::OptionsScreen(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 150));
    title.setFont(font);
    title.setString("Options");
    title.setColor(sf::Color::White);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 220), sf::Vector2f(120, 30), "Back", font);
    buttons.at(selection).set_focused(true);
}

OptionsScreen::~OptionsScreen()
{
    std::cout << "OptionsScreen destroyed\n";
}

GameState* OptionsScreen::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                destroyed = true;
            }
            else if (event.key.code == sf::Keyboard::Return) {
                destroyed = true; // Temporary
            }
        }
    }

    return nullptr;
}

void OptionsScreen::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
    window.draw(title);
}