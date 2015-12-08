
#include "Player.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Utilities.h"
#include "LevelSelect.h"
#include "OptionsScreen.h"
#include "HighscoresScreen.h"

MainMenu::MainMenu(Game *game)
{
    this->game = game;
    game->reset_view();
    font.loadFromFile("HATTEN.ttf");
    title = centered_text("Main Menu", WINDOW_WIDTH / 2, 40, font);

    borders.setPosition(sf::Vector2f(WINDOW_WIDTH / 4 - 70, 130));
    borders.setSize(sf::Vector2f(140, 180));
    borders.setOutlineThickness(2.f);
    borders.setOutlineColor(sf::Color::White);
    borders.setFillColor(sf::Color::Transparent);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 140), sf::Vector2f(120, 30), "Start", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 180), sf::Vector2f(120, 30), "Options", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 220), sf::Vector2f(120, 30), "Highscores", font);
    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 260), sf::Vector2f(120, 30), "Quit", font);
    buttons.at(selection).set_focused(true);

    music.openFromFile("sounds/POL-fortress-short.wav");
    music.setVolume(33);
    //music.play();

    Player *player = new Player(WINDOW_WIDTH / 3 * 2, WINDOW_HEIGHT / 2, 64.f, 64.f, this);
    player->setDemostate();
    entities.push_back(player);
}

MainMenu::~MainMenu()
{
    music.stop();
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
    }
}

GameState* MainMenu::update()
{
    if (music.getStatus() == sf::Music::Stopped) music.play();

    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)  destroyed = true;
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                destroyed = true;
                break;

            case sf::Keyboard::Up:
                buttons.at(selection--).set_focused(false);
                if (selection < 0) selection = buttons.size() - 1;
                buttons.at(selection).set_focused(true);
                break;

            case sf::Keyboard::Down:
                buttons.at(selection++).set_focused(false);
                if (selection >= buttons.size()) selection = 0;
                buttons.at(selection).set_focused(true);
                break;

            case sf::Keyboard::Return:
                switch (selection)
                {
                case 0:
                    return new LevelSelect(game);

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
                break;
            }
        }
    }
    
    float delta = 0.0;
    for (Entity *e : entities) e->update(delta);

    return nullptr;
}

void MainMenu::draw(sf::RenderWindow &window)
{
    window.draw(title);
    window.draw(borders);
    for (Button b : buttons) b.draw(window);
    for (Entity *e : entities) e->draw(window);
}