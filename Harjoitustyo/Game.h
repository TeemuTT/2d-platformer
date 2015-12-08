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
    sf::RenderWindow& get_window();
    AssetManager* get_asset_manager();
private:
    sf::RenderWindow window;
    AssetManager asset_manager;
    std::stack<GameState*> states;
};

#endif