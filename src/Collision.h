#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

class Collision {
private:
public:
    static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

#endif