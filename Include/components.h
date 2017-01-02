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

#define COREFLAG_ACTIVE         1
#define COREFLAG_OCCUPIED       1<<2

struct CoreComponent
{
    string name;
    u32 flags;
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

struct AnimatedSpriteComponent
{
    u32 frameWidth;
    r32 framesPerSecond;
    r32 timer = 0.0f;
    // TODO: flags?
    bool oneShot = true;
};

struct TextComponent
{
    string text;
};

struct PhysicsComponent
{
    Vec2 velocity;
    r32 drag = 0.0f;
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
