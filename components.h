#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ttmath.h"
#include "texture2d.h"

enum RectPivot
{
    RECTPIVOT_CENTER,
    RECTPIVOT_TOPLEFT,
    RECTPIVOT_TOPRIGHT,
    RECTPIVOT_BOTTOMLEFT,
    RECTPIVOT_BOTTOMRIGHT,
};

struct TransformComponent
{
    Vec2 localPosition;
    Vec2 position;
    Vec2 scale;
    r32 rotation;
    bool dirty = true;
    i32 parent = -1;
    Mat4 modelMatrix;
};

struct NameComponent
{
    string name;
};

struct RectTransformComponent
{
    RectPivot pivot;
    RectPivot anchor;
    Vec2 size;
};

struct SpriteComponent
{
    Texture2D* texture;
    //RectPivot pivot;
    //RectPivot anchor;
    //i32 parent = -1;
    bool isVisible;

    u32 width;
    u32 height;
};

struct TextComponent
{
    string text;
};

#endif // COMPONENTS_H
