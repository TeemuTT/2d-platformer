
#include "Game.h"
#include "GameScreen.h"
#include "MainMenu.h"

int main()
{
    Game game;
    game.push_state(new MainMenu(&game));
    game.run();

    return 0;
}
