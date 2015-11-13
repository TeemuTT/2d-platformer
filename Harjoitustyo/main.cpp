
#include "Game.h"
#include "GameScreen.h"

int main()
{
    Game game;
    game.push_state(new GameScreen(&game));
    game.run();

    return 0;
}