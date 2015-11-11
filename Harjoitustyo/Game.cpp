#include "Game.h"
#include "GameState.h"

Game::Game()
{
    window.create(sf::VideoMode(480, 360), "SFML");
    window.setFramerateLimit(60);
}

Game::~Game()
{
    while (states.size() != 0) {
        delete states.top();
        states.pop();
    }
    std::cout << "Game destroyed\n";
}

void Game::push_state(GameState* state)
{
    states.push(state);
}

GameState* Game::peek()
{
    if (!states.empty()) return states.top();
    return nullptr;
}

void Game::run()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        GameState* state = peek();
        if (state == nullptr) {
            window.close();
            break;
        }
        state->update();

        window.clear();
        state->draw(window);
        window.display();
    }
}