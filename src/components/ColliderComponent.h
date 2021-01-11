#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>

#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"

class ColliderComponent : public Component
{
private:
public:
    std::string colliderTag;
    SDL_Texture *texture;
    SDL_Rect collider;
    SDL_Rect sourceRect;
    SDL_Rect destRect;

    TransformComponent *transform;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
    {
        this->colliderTag = colliderTag;
        this->collider = {x, y, width, height};
        SetTexture("collision-texture");
    }

    void SetTexture(std::string assetTextureId)
    {
        texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Initialize() override
    {
        if (owner->HasComponent<TransformComponent>())
        {
            transform = owner->GetComponent<TransformComponent>();
            sourceRect = {0, 0, transform->width, transform->height};
            destRect = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override
    {
        if (owner->HasComponent<TransformComponent>())
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;

            destRect.x = collider.x - Game::camera.x;
            destRect.y = collider.y - Game::camera.y;
        }
    }

    void Render() override
    {
        if (owner->IsDebug())
        {
            TextureManager::Draw(texture, sourceRect, destRect, SDL_FLIP_NONE);
        }
    }
};

#endif