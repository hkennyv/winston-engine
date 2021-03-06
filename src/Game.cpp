#include "../lib/glm/glm.hpp"
#include <iostream>

#include "./AssetManager.h"
#include "./Constants.h"
#include "./Game.h"
#include "./Map.h"
#include "./components/ColliderComponent.h"
#include "./components/SpriteComponent.h"
#include "./components/TransformComponent.h"
#include "./components/KeyboardControlComponent.h"
#include "./components/TileComponent.h"

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);

SDL_Renderer *Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

Map* map;

Game::Game() { this->isRunning = false; }

Game::~Game() {}

bool Game::IsRunning() const { return this->isRunning; }

void Game::Initialize(int width, int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL." << std::endl;
    return;
  }

  window =
      SDL_CreateWindow("winston engine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

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

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
  // Start including new assets to assetmanager
  assetManager->AddTexture(
      "tank-image", std::string("./assets/images/tank-big-right.png").c_str());
  assetManager->AddTexture(
      "chopper-image",
      std::string("./assets/images/chopper-spritesheet.png").c_str());
  assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
  assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
  assetManager->AddTexture("collision-texture", std::string("./assets/images/collision-texture.png").c_str());

  map = new Map(std::string("jungle-tiletexture"), 2, 32);
  map->LoadMap(std::string("./assets/tilemaps/jungle.map"), 25, 20);

  // start including entities and components to them
  // make sure to put `KeyboardControlComponent` LAST
  // Entity& chopperEntity(manager.AddEntity("chopper", PLAYER_LAYER));
  player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
  player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
  player.AddComponent<ColliderComponent>("player", 240, 106, 32, 32);
  player.AddComponent<KeyboardControlComponent>("w", "s", "d", "a", " ", "f2");

  Entity &tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
  tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
  tankEntity.AddComponent<SpriteComponent>("tank-image");
  tankEntity.AddComponent<ColliderComponent>("enemy", 0, 0, 32, 32);

  Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
  radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

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

  HandleCameraMovement();
  CheckCollisions();
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  if (manager.HasNoEntities())
    return;

  manager.Render();

  SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
  TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

  camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
  camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

  camera.x = camera.x < 0 ? 0 : camera.x;
  camera.y = camera.y < 0 ? 0 : camera.y;

  camera.x = camera.x > camera.w ? camera.w : camera.x;
  camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
  std::string collisionTagType = manager.CheckEntityCollisions(player);

  if (collisionTagType.compare("enemy") == 0) {
    // TODO: do something when collision is identified with an enemy
    isRunning = false;
  }
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
