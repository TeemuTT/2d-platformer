
#include <iostream>

#include "MainMenu.h"
#include "LevelSelect.h"
#include "OptionsScreen.h"
#include "HighscoresScreen.h"
#include "Constants.h"
#include "Player.h"

MainMenu::MainMenu(Game *game)
{
    this->game = game;
    game->reset_view();
    font.loadFromFile("HATTEN.ttf");

    title.setFont(font);
    title.setString("Main Menu");
    title.setColor(sf::Color::White);
    title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 40));

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 140), sf::Vector2f(120, 30), "Start", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 180), sf::Vector2f(120, 30), "Options", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 220), sf::Vector2f(120, 30), "Highscores", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 260), sf::Vector2f(120, 30), "Quit", font);
    buttons.at(selection).set_focused(true);

    music.openFromFile("menu.wav");
    music.setVolume(33);
    music.play();

    Player *player = new Player(WINDOW_WIDTH / 3 * 2, WINDOW_HEIGHT / 2, 64.f, 64.f, this);
    player->setDemostate();
    entities.push_back(player);
}

MainMenu::~MainMenu()
{
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
        //std::cout << "deleted entity.\n";
    }
    std::cout << "mainmenu destroyed\n";
}

GameState* MainMenu::update()
{
    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            destroyed = true;
        }
        else if (event.type == sf::Event::KeyPressed) {
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
                    return new LevelSelect(game);
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
    
    float delta = 0.0;
    for (Entity *e : entities) e->update(delta);

    return nullptr;
}

void MainMenu::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) {
        b.draw(window);
    }
    window.draw(title);
    for (Entity *e : entities) e->draw(window);
}