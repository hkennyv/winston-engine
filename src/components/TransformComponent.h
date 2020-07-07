#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Game.h"

class TransformComponent : public Component {
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int width;
  int height;
  int scale;

  TransformComponent(int posX, int posY, int velX, int velY, int w, int h,
                     int s) {
    name = "TransformComponent";
    position = glm::vec2(posX, posY);
    velocity = glm::vec2(velX, velY);
    width = w;
    height = h;
    scale = s;
  }

  void Initialize() override {}

  void Update(float deltaTime) override {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // TODO: clamping boundaries DOESN'T factor in SCALE
    if (position.x > (WINDOW_WIDTH - 1 - width))
      position.x = WINDOW_WIDTH - 1 - width;

    if (position.x < 0)
      position.x = 0;

    if (position.y > (WINDOW_HEIGHT - 1 - height))
      position.y = WINDOW_HEIGHT - 1 - height;

    if (position.y < 0)
      position.y = 0;
  }

  void Render() override {

  }
};

#endif
