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
    bool isVisible;
    RectPivot pivot;
    u32 width;
    u32 height;
};

struct TextComponent
{
    string text;
};

struct PhysicsComponent
{
    Vec2 velocity;
    //r32 angularVelocity;
};

#define COLLISIONFUNC(name) void name(u32 current, u32 other, void* userData)
typedef COLLISIONFUNC(CollisionCallback_t);

struct ColliderComponent
{
    bool enabled;
    CollisionCallback_t *collisionCallback = 0;
    void* userData;
};

#endif // COMPONENTS_H
