#include <iostream>
#include "../lib/glm/glm.hpp"

#include "./Constants.h"
#include "./Game.h"
#include "./components/TransformComponent.h"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return this->isRunning;
}


void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
            "winston engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Error creating SDL Window." << std::endl;
        return;
    }

    // -1 uses default renderer and 0 no options
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        std::cerr << "Error creating SDL Renderer." << std::endl;
    }

    isRunning = true;

    LoadLevel(0);

    std::cout << "Initialization complete! :)" << std::endl;
    return;
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        default:
            break;
    }
}


void Game::LoadLevel(int levelNumber) {
    // TODO: add entities and add components to entities
    Entity& newEntity1(manager.AddEntity("projectile1"));
    newEntity1.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);

    Entity& newEntity2(manager.AddEntity("projectile2"));
    newEntity2.AddComponent<TransformComponent>(0, 0, 10, 10, 22, 22, 1);

    Entity& newEntity3(manager.AddEntity("projectile3"));
    newEntity3.AddComponent<TransformComponent>(800, 600, -20, -5, 12, 12, 1);

    manager.ListAllEntities();
}


void Game::Update() {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // dt is difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // sets new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) return;

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

