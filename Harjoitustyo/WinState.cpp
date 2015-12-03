
#include "WinState.h"
#include "MainMenu.h"
#include "Constants.h"

#include <fstream>
#include <iostream>

WinState::WinState(Game *game, bool win, int score)
{
    this->game = game;
    this->win = win;
    this->score = score;
    game->reset_view();
    font.loadFromFile("HATTEN.ttf");

    label.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 60, 40));
    label.setFont(font);
    label.setColor(sf::Color::White);
    switch (win)
    {
    case true:
        label.setString("Level cleared!");
        break;
    case false:
        label.setString("You have died.");
    default:
        break;
    }    
    
    prompt.setFont(font);
    prompt.setString("Press Enter to continue.");
    prompt.setColor(sf::Color::White);
    prompt.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - prompt.getGlobalBounds().width / 2, 350));

    nameprompt.setFont(font);
    nameprompt.setString("Enter a name: ");
    nameprompt.setColor(sf::Color::White);
    nameprompt.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - nameprompt.getGlobalBounds().width, 200));

    scoretext.setFont(font);
    scoretext.setString("You got a score of " + std::to_string(score));
    scoretext.setColor(sf::Color::White);
    scoretext.setPosition(sf::Vector2f(sf::Vector2f(WINDOW_WIDTH / 2 - scoretext.getGlobalBounds().width / 2, 150)));

    nametext.setFont(font);
    nametext.setColor(sf::Color::White);
    nametext.setPosition(sf::Vector2f(sf::Vector2f(WINDOW_WIDTH / 2 - nametext.getGlobalBounds().width / 2, 200)));

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
}



WinState::~WinState()
{
    if (name.length() == 0) return;
    std::ofstream file("scores.dat", std::ios::out | std::ios::binary | std::ios::app);
    if (file.is_open()) {
        file << name << " ";
        file << score;
    }
}

GameState* WinState::update()
{
    alpha -= 3;
    if (alpha <= 0) alpha = 0;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));

    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Return) {
                return new MainMenu(game);
            }
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) {
                name = name.substr(0, name.length() - 1);
            }
            else if (name.length() < 15) {
                name += (char)event.text.unicode;
            }
            nametext.setString(name);
        }
    }

    return nullptr;
}

void WinState::draw(sf::RenderWindow &window)
{
    window.draw(label);
    window.draw(prompt);
    window.draw(scoretext);
    window.draw(nametext);
    window.draw(nameprompt);
    window.draw(fillRect);
}

void WinState::transition()
{

}