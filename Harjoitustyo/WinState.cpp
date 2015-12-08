
#include <fstream>

#include "WinState.h"
#include "MainMenu.h"
#include "Utilities.h"
#include "Constants.h"

WinState::WinState(Game *game, bool win, int score) : win(win), score(score)
{
    this->game = game;
    game->reset_view();
    font.loadFromFile("HATTEN.ttf");
    
    label = centered_text("Level cleared!", WINDOW_WIDTH / 2, 40, font);
    win ? label.setString("Level cleared!") : label.setString("You have died.");
    prompt = centered_text("Press Enter to continue.", WINDOW_WIDTH / 2, 350, font);
    nameprompt = centered_text("Enter a name: ", WINDOW_WIDTH / 2 - 100, 200, font);
    scoretext = centered_text("You got a score of " + std::to_string(score), WINDOW_WIDTH / 2, 150, font);
    nametext = centered_text("E", WINDOW_WIDTH / 2, 200, font);
    nametext.setString("");

    fillRect.setPosition(sf::Vector2f(0, 0));
    fillRect.setSize(sf::Vector2f(1500, 1500));
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));
}



WinState::~WinState()
{
    // Write highscore to file is name is entered.
    if (name.length() == 0) return;
    std::ofstream file("scores.dat", std::ios::out | std::ios::binary | std::ios::app);
    if (file.is_open()) {
        file << name << " ";
        file << score;
    }
}

GameState* WinState::update()
{
    // Fade in.
    alpha -= 3;
    if (alpha <= 0) alpha = 0;
    fillRect.setFillColor(sf::Color(0, 0, 0, alpha));

    sf::Event event;
    while (game->window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Return)
                return new MainMenu(game);

        // Update name field.
        if (event.type == sf::Event::TextEntered) {

            if (event.text.unicode == 8)
                name = name.substr(0, name.length() - 1);

            else if (event.text.unicode < 127 && event.text.unicode > 32 && name.length() < 15)
                name += (char)event.text.unicode;

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
