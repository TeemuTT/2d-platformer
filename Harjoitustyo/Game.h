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
    GameState* peek();

private:
    sf::RenderWindow window;
    std::stack<GameState*> states;
};

#endif