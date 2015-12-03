
#include "LevelSelect.h"
#include "GameScreen.h"
#include "MainMenu.h"
#include "Constants.h"

LevelSelect::LevelSelect(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    text.setFont(font);
    text.setString("Select stage");
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 40));

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 400), sf::Vector2f(120, 30), "Back", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 100), sf::Vector2f(120, 30), "Stage 1", font);
    buttons.at(selection).set_focused(true);
}

LevelSelect::~LevelSelect()
{

}

GameState* LevelSelect::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                return new MainMenu(game);
            }
            else if (event.key.code == sf::Keyboard::Up) {
                buttons.at(selection).set_focused(false);
                selection--;
                if (selection < 0) selection = 1;
                buttons.at(selection).set_focused(true);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                buttons.at(selection).set_focused(false);
                selection++;
                if (selection > 1) selection = 0;
                buttons.at(selection).set_focused(true);
            }
            else if (event.key.code == sf::Keyboard::Return) {
                switch (selection)
                {
                case 0:
                    return new MainMenu(game);
                case 1:
                    return new GameScreen(game, "level_1");
                }
            }
        }
    }

    return nullptr;
}

void LevelSelect::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
    window.draw(text);
}