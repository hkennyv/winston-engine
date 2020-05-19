#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include <SDL2/SDL.h>

int main(int argc, char *args[]) {
    std::cout << "Game is running..." << std::endl;

    Game* game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning()) {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();

    return 0;
}

