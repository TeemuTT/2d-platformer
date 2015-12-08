
#include "MainMenu.h"
#include "Utilities.h"
#include "Constants.h"
#include "GameScreen.h"
#include "LevelSelect.h"

LevelSelect::LevelSelect(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    text = centered_text("Select stage", WINDOW_WIDTH / 2, 40, font);

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
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                return new MainMenu(game);

            case sf::Keyboard::Up:
                buttons.at(selection--).set_focused(false);
                if (selection < 0) selection = 1;
                buttons.at(selection).set_focused(true);
                break;

            case sf::Keyboard::Down:
                buttons.at(selection++).set_focused(false);
                if (selection > 1) selection = 0;
                buttons.at(selection).set_focused(true);
                break;

            case sf::Keyboard::Return:
                switch (selection) {
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
    for (Button b : buttons) b.draw(window);
    window.draw(text);
}