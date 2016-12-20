#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ttmath.h"
#include "texture2d.h"

enum SpritePivot
{
    SPRITEPIVOT_CENTER,
    SPRITEPIVOT_TOPLEFT,
    SPRITEPIVOT_TOPRIGHT,
    SPRITEPIVOT_BOTTOMLEFT,
    SPRITEPIVOT_BOTTOMRIGHT,
};

struct TransformComponent
{
    Vec2 localPosition;
    Vec2 position;
    Vec2 scale;
    r32 rotation;
    bool dirty = true;
    Mat4 modelMatrix;
};

struct SpriteComponent
{
    Texture2D* texture;
    SpritePivot pivot;
    SpritePivot anchor;
    i32 parent = -1;
    bool isVisible;

    u32 width;
    u32 height;
};

#endif // COMPONENTS_H
