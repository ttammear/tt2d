#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include <array>
#include <map>

#include "shared.h"
#include "components.h"
#include "opengltexture2d.h"
#include "componentmanager.h"
#include "spriterendersystem.h"
#include "textrendersystem.h"
#include "transformsystem.h"
#include "physicssystem.h"
#include "renderer.h"
#include "openglrenderer.h"
#include "input.h"
#include "collisionsystem.h"

using std::vector;
using std::array;
using std::string;

using Entity = u32;

class Engine
{
public:
    Engine();
    Engine(const Engine& that) = delete;
    Engine & operator=(const Engine&) = delete;
    ~Engine();
    void Init(u32 width, u32 height);
    void Update(r32 dt);
    Entity CreateScreenEntity(string name, RectPivot pivot, RectPivot anchor, u32 parent);
    Entity CreateUISprite(string name, string pathToTexture, RectPivot pivot, RectPivot anchor, u32 parent = -1);
    Entity CreateUIText(string name, string text, r32 scale, RectPivot pivot, RectPivot anchor, u32 parent = -1);

    Entity CreateSprite(string name, string pathToTexture, RectPivot pivot);
    Entity CreateAnimatedSprite(string name, string pathToTexture, u32 frames, r32 framesPerSecond, RectPivot pivot);

    Texture2D* GetTexture(string path);

    void SetGameProjection(Mat4& mat);

    void SetScreenSize(IVec2 size);
    Renderer* GetRenderer();

    SpriteRenderSystem _spriteRenderSystem;
    TextRenderSystem _textRenderSystem;
    TransformSystem _transformSystem;
    PhysicsSystem _physicsSystem;
    CollisionSystem _collisionSystem;
    ComponentManager _components;

    Input _input;

private:

    Renderer* _renderer;
    bool _initialized = false;
    std::map<std::string, Texture2D*> _textureCache;
};

#endif // ENGINE_H
