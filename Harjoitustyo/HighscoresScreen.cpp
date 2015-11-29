
#include <iostream>

#include "HighscoresScreen.h"
#include "Constants.h"

HighscoresScreen::HighscoresScreen(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 40));
    title.setFont(font);
    title.setString("Highscores");
    title.setColor(sf::Color::White);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 220), sf::Vector2f(120, 30), "Back", font);
    buttons.at(selection).set_focused(true);
}

HighscoresScreen::~HighscoresScreen()
{
    std::cout << "HighscoresScreen destroyed\n";
}

GameState* HighscoresScreen::update()
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

void HighscoresScreen::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
    window.draw(title);
}