
#include "LevelSelect.h"
#include "GameScreen.h"
#include "MainMenu.h"
#include "Constants.h"

LevelSelect::LevelSelect(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 40));
    text.setFont(font);
    text.setString("Select stage");
    text.setColor(sf::Color::White);

    text2.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 150));
    text2.setFont(font);
    text2.setString("Stage 1");
    text2.setColor(sf::Color::White);

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
            else if (event.key.code == sf::Keyboard::Return) {
                return new GameScreen(game, "level_1.txt");
            }
        }
    }

    return nullptr;
}

void LevelSelect::draw(sf::RenderWindow &window)
{
    window.draw(text);
    window.draw(text2);
}