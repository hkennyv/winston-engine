#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>

#include "../Animation.h"
#include "./TransformComponent.h"

class SpriteComponent : public Component {
private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect sourceRect;
  SDL_Rect destRect;

  // attributes let us know if it is animated, how many frames, and how fast
  // it is animated, or if it is always fixed
  bool isAnimated;
  bool isFixed;

  int numFrames;
  int animationSpeed;

  // this map keeps track of all the animations for the sprite
  std::map<std::string, Animation> animations;
  std::string currentAnimationName;
  unsigned int animationIndex = 0;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent(std::string assetTextureId) {
    SetTexture(assetTextureId);
    isFixed = false;
    isAnimated = false;
  }

  SpriteComponent(std::string assetTextureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
    this->isAnimated = true;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
    this->isFixed = isFixed;

    if (hasDirections) {
      Animation downAnimation = Animation(0, numFrames, animationSpeed);
      Animation rightAnimation = Animation(1, numFrames, animationSpeed);
      Animation leftAnimation = Animation(2, numFrames, animationSpeed);
      Animation upAnimation = Animation(3, numFrames, animationSpeed);

      animations.emplace("DownAnimation", downAnimation);
      animations.emplace("RightAnimation", rightAnimation);
      animations.emplace("LeftAnimation", leftAnimation);
      animations.emplace("UpAnimation", upAnimation);

      // Assume we always start with down
      this->animationIndex = 0;
      this->currentAnimationName = "DownAnimation";

    } else {
      Animation singleAnimation = Animation(0, numFrames, animationSpeed);
      animations.emplace("SingleAnimation", singleAnimation);

      this->animationIndex = 0;
      this->currentAnimationName = "SingleAnimation";
    }

    Play(this->currentAnimationName);
    SetTexture(assetTextureId);
  }

  void Play(std::string animationName) {
    numFrames = animations[animationName].numFrames;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
    currentAnimationName = animationName;
  }

  void SetTexture(std::string assetTextureId) {
    name = "SpriteComponent";
    texture = Game::assetManager->GetTexture(assetTextureId);
  }

  void Initialize() override {
    transform = owner->GetComponent<TransformComponent>();
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = transform->width;
    sourceRect.h = transform->height;
  }

  void Update(float deltaTime) override {
    // handle animation
    if (isAnimated) {
      sourceRect.x = sourceRect.w * ((static_cast<int>(SDL_GetTicks() / animationSpeed)) % numFrames);
    }
    sourceRect.y = animationIndex * transform->height;

    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
  }

  void Render() override {
    TextureManager::Draw(texture, sourceRect, destRect, spriteFlip);
  }
};

#endif
