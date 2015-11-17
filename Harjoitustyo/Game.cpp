
#include <iostream>

#include "Constants.h"
#include "Game.h"
#include "GameState.h"

Game::Game()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window.setFramerateLimit(FPSLIMIT);

    //std::cout << "view: " << window.getView().getViewport().left << ", " << window.getView().getViewport().left << std::endl;
}

Game::~Game()
{
    while (states.size() != 0) {
        pop_state();
    }
    std::cout << "Game destroyed\n";
}

void Game::push_state(GameState* state)
{
    states.push(state);
}

void Game::pop_state()
{
    delete states.top();
    states.pop();
    window.setView(window.getDefaultView());
    std::cout << "view: " << window.getView().getViewport().left << ", " << window.getView().getViewport().left << std::endl;
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
        else if (state->isDestroyed()) {
            pop_state();
            continue;
        }
        
        GameState *state_ = state->update();
        
        if (state_ != nullptr) {
            pop_state();
            push_state(state_);
            continue;
        }

        window.clear();
        state->draw(window);
        window.display();
    }
}

void Game::set_view(sf::View &view)
{
    window.setView(view);
}

void Game::reset_view()
{
    window.setView(window.getDefaultView());
}

sf::Window* Game::get_window()
{
    return &window;
}