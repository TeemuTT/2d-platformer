#ifndef __GAME__
#define __GAME__

#include <stack>
#include <SFML/Graphics.hpp>

#include "AssetManager.h"

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void push_state(GameState* state);
    void pop_state();
    GameState* top();
    void set_view(sf::View &view);
    void reset_view();
    sf::Window* get_window();
    sf::RenderWindow window;
    AssetManager* get_asset_manager();
private:
    std::stack<GameState*> states;
    AssetManager asset_manager;
};

#endif