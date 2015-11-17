
#include <iostream>

#include "MainMenu.h"
#include "GameScreen.h"

MainMenu::MainMenu(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    startButton = Button{ sf::Vector2f(100, 100), sf::Vector2f(120, 30), "Start", font};
    optionsButton = Button{ sf::Vector2f(100, 140), sf::Vector2f(120, 30), "Options", font };
    highscoresButton = Button{ sf::Vector2f(100, 180), sf::Vector2f(120, 30), "Highscores", font };
    quitButton = Button{ sf::Vector2f(100, 220), sf::Vector2f(120, 30), "Quit", font };
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i point = sf::Mouse::getPosition(*(game->get_window()));

        if (startButton.isClicked(point)) {
            return new GameScreen(game);
        }
        else if (optionsButton.isClicked(point)) {
            
        }
        else if (highscoresButton.isClicked(point)) {
            
        }
        else if (quitButton.isClicked(point)) {
            destroyed = true;
        }
    }

    return nullptr;
}

void MainMenu::draw(sf::RenderWindow &window)
{
    startButton.draw(window);
    optionsButton.draw(window);
    highscoresButton.draw(window);
    quitButton.draw(window);
}