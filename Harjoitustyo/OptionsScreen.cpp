
#include "Utilities.h"
#include "Constants.h"
#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(Game *game)
{
    this->game = game;
    font.loadFromFile("HATTEN.ttf");
    title = centered_text("Option", WINDOW_WIDTH / 2, 40, font);

    buttons.emplace_back(sf::Vector2f(WINDOW_WIDTH / 4, 400), sf::Vector2f(120, 30), "Back", font);
    buttons.at(selection).set_focused(true);
}

OptionsScreen::~OptionsScreen()
{

}

GameState* OptionsScreen::update()
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
            }
        }
    }

    return nullptr;
}

void OptionsScreen::draw(sf::RenderWindow &window)
{
    for (Button b : buttons) b.draw(window);
    window.draw(title);
}