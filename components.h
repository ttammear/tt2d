#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ttmath.h"
#include "texture2d.h"

struct TransformComponent
{
    Vec2 position;
    Vec2 scale;
    r32 rotation;
};

struct SpriteComponent
{
    Texture2D* texture;
    bool isVisible;
};

#endif // COMPONENTS_H
