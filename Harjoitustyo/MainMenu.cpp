
#include <iostream>

#include "MainMenu.h"
#include "GameScreen.h"
#include "OptionsScreen.h"
#include "HighscoresScreen.h"
#include "Constants.h"

MainMenu::MainMenu(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 40));
    title.setFont(font);
    title.setString("Main Menu");
    title.setColor(sf::Color::White);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 100), sf::Vector2f(120, 30), "Start", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 140), sf::Vector2f(120, 30), "Options", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 180), sf::Vector2f(120, 30), "Highscores", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 220), sf::Vector2f(120, 30), "Quit", font);
    buttons.at(selection).set_focused(true);
}

MainMenu::~MainMenu()
{
    std::cout << "mainmenu destroyed\n";
}

GameState* MainMenu::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                destroyed = true;
            }
            else if (event.key.code == sf::Keyboard::Up) {
                buttons.at(selection).set_focused(false);
                selection--;
                if (selection < 0) selection = 3;
                buttons.at(selection).set_focused(true);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                buttons.at(selection).set_focused(false);
                selection++;
                if (selection > 3) selection = 0;
                buttons.at(selection).set_focused(true);
            }
            else if (event.key.code == sf::Keyboard::Return) {
                switch (selection)
                {
                case 0:
                    return new GameScreen(game);
                    break;
                case 1:
                    game->push_state(new OptionsScreen(game));
                    break;
                case 2:
                    game->push_state(new HighscoresScreen(game));
                    break;
                case 3:
                    destroyed = true;
                    break;
                }
            }
        }
    }

    return nullptr;
}

void MainMenu::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
    window.draw(title);
}