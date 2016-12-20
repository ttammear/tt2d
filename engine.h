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
    void Update(r32 dt);
    Entity CreateEntity(string name);
    Entity CreateSprite(string name, string pathToTexture, SpritePivot pivot, SpritePivot anchor, u32 parent = -1);
    void SetLocalPosition(Entity entity, Vec2 position);
    void SetRotation(Entity entity, r32 rotation);
    void SetScale(Entity entity, Vec2 scale);

private:

    u32 _entityPtr = 0;
    ComponentManager _components;
    SpriteRenderSystem _spriteRenderSystem;
    Renderer _renderer;
};

#endif // ENGINE_H
