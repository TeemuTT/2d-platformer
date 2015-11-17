#ifndef __GAME__
#define __GAME__

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void push_state(GameState* state);
    void pop_state();
    GameState* peek();
    void set_view(sf::View &view);
    void reset_view();
    sf::Window* get_window();
    sf::RenderWindow window;
private:
    std::stack<GameState*> states;
};

#endif