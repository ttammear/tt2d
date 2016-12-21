#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include <array>

#include "shared.h"
#include "components.h"
#include "opengltexture2d.h"
#include "componentmanager.h"
#include "spriterendersystem.h"
#include "textrendersystem.h"
#include "transformsystem.h"
#include "renderer.h"

using std::vector;
using std::array;
using std::string;

using Entity = u32;

class Engine
{
public:
    Engine();
    ~Engine();
    void Init();
    void Update(r32 dt);
    Entity CreateEntity(string name);
    Entity CreateScreenEntity(string name, RectPivot pivot, RectPivot anchor, u32 parent);
    Entity CreateSprite(string name, string pathToTexture, RectPivot pivot, RectPivot anchor, u32 parent = -1);
    Entity CreateText(string name, string text, r32 scale, RectPivot pivot, RectPivot anchor, u32 parent = -1);
    void SetLocalPosition(Entity entity, Vec2 position);
    void SetRotation(Entity entity, r32 rotation);
    void SetScale(Entity entity, Vec2 scale);

private:

    u32 _entityPtr = 0;
    ComponentManager _components;
    SpriteRenderSystem _spriteRenderSystem;
    TextRenderSystem _textRenderSystem;
    TransformSystem _transformSystem;
    Renderer _renderer;
    //Text _text;
};

#endif // ENGINE_H
