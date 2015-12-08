
#include "Game.h"
#include "GameState.h"
#include "Constants.h"

Game::Game()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window.setFramerateLimit(FPSLIMIT);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
}

Game::~Game()
{
    while (states.size() != 0) {
        pop_state();
    }
}

void Game::push_state(GameState* state)
{
    states.push(state);
}

void Game::pop_state()
{
    delete states.top();
    states.pop();
}

GameState* Game::top()
{
    if (!states.empty()) return states.top();
    return nullptr;
}

void Game::run()
{
    while (window.isOpen()) {

        GameState* state = top();
        if (state == nullptr) {
            window.close();
            break;
        }
        else if (state->isDestroyed()) {
            pop_state();
            continue;
        }
        
        GameState *new_state = state->update();
        
        if (new_state != nullptr) {
            pop_state();
            push_state(new_state);
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

AssetManager* Game::get_asset_manager()
{
    return &asset_manager;
}