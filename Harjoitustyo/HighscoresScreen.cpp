
#include <iostream>
#include <fstream>

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

    
    scoretext.setFont(font);
    scoretext.setColor(sf::Color::White);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 2, 400), sf::Vector2f(120, 30), "Back", font);
    buttons.at(selection).set_focused(true);

    std::ifstream file("scores.dat", std::ios::in | std::ios::binary);
    std::string name;
    int score;
    if (file.is_open()) {
        while (file >> name) {
            file >> score;
            scores.insert(std::pair<int, std::string>(score, name));
        }
    }
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
                destroyed = true;
            }
            else if (event.key.code == sf::Keyboard::Delete) {
                scores.clear();
                std::ofstream file("scores.dat", std::ios::out | std::ios::binary | std::ios::trunc);
                file.close();
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
    
    int i = 0;
    for (auto a = scores.rbegin(); a != scores.rend(); ++a) {
        scoretext.setString(a->second + " : " + std::to_string(a->first));
        scoretext.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 80 + i * 30));
        i++;
        window.draw(scoretext);
    }
}