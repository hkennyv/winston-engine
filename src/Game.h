#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;

public:
    Game();
    ~Game();

    bool IsRunning() const;
    void Initialize(int widht, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
