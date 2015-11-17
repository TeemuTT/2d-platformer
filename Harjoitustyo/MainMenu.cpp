
#include <iostream>

#include "MainMenu.h"
#include "GameScreen.h"
#include "Constants.h"

MainMenu::MainMenu(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escape_toggled) {
        destroyed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) escape_toggled = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up_toggled) {
        buttons.at(selection).set_focused(false);
        selection--;
        if (selection < 0) selection = 3;
        buttons.at(selection).set_focused(true);
        up_toggled = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down_toggled) {
        buttons.at(selection).set_focused(false);
        selection++;
        if (selection > 3) selection = 0;
        buttons.at(selection).set_focused(true);
        down_toggled = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) down_toggled = true;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) up_toggled = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
        switch (selection)
        {
        case 0:
            return new GameScreen(game);
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            destroyed = true;
            break;
        }
    }

    return nullptr;
}

void MainMenu::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
}