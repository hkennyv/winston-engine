#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"

class AssetManager;

class Game {
private:
    SDL_Window* window;

    bool isRunning;

public:
    Game();
    ~Game();

    static SDL_Renderer* renderer;
    static AssetManager* assetManager;
    static SDL_Event event;
    static SDL_Rect camera;

    int ticksLastFrame;
    void LoadLevel(int levelNumber);
    bool IsRunning() const;
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void HandleCameraMovement();
    void CheckCollisions();
    void Destroy();
};

#endif
