
#include <fstream>

#include "Utilities.h"
#include "Constants.h"
#include "HighscoresScreen.h"

HighscoresScreen::HighscoresScreen(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");

    title = centered_text("Highscores", WINDOW_WIDTH / 2, 40, font);
    scoretext = centered_text("Highscores", WINDOW_WIDTH / 2, 0, font);

    button = Button(sf::Vector2f(WINDOW_WIDTH / 4, 400), sf::Vector2f(120, 30), "Back", font);
    button.set_focused(true);

    int score;
    std::string name;
    std::ifstream file("scores.dat", std::ios::in | std::ios::binary);
    if (file.is_open()) {
        while (file >> name) {
            file >> score;
            scores.insert(std::pair<int, std::string>(score, name));
        }
    }
}

HighscoresScreen::~HighscoresScreen()
{

}

GameState* HighscoresScreen::update()
{
    sf::Event event;
    while (game->get_window().pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Return:
                destroyed = true;
                break;

            case sf::Keyboard::Delete:
                scores.clear();
                std::ofstream file("scores.dat", std::ios::out | std::ios::binary | std::ios::trunc);
                break;
            }
        }
    }

    return nullptr;
}

void HighscoresScreen::draw(sf::RenderWindow &window)
{
    button.draw(window);
    window.draw(title);

    int i = 0;
    for (auto a = scores.rbegin(); a != scores.rend(); ++a, ++i) {
        scoretext.setString(a->second + "    " + std::to_string(a->first));
        scoretext.setPosition(sf::Vector2f(scoretext.getPosition().x, 80 + i * 30));
        window.draw(scoretext);
    }
}