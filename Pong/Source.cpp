#include "Game.h"

int main(int arc, char* argv[]) {

    // Detect memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Game game;

    if (game.Init()) {
        game.GameLoop();
    }

    game.Shutdown();
    

    return 0;
}
