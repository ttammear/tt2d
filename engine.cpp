#include "engine.h"

Engine::Engine()
{
    _spriteRenderSystem.Init(&_components, &_renderer);
}

Engine::~Engine()
{

}

void Engine::Update(r32 dt)
{
    _spriteRenderSystem.Update();
}

void Engine::SetLocalPosition(Entity entity, Vec2 position)
{
    _components.transforms[entity].localPosition = position;
}

void Engine::SetScale(Entity entity, Vec2 scale)
{
    _components.transforms[entity].scale = scale;
}

void Engine::SetRotation(Entity entity, r32 rotation)
{
    _components.transforms[entity].rotation = rotation;
}

Entity Engine::CreateEntity(string name)
{
    Entity entity = _entityPtr++;
    _components.masks[entity] = COMPONENT_NONE;
    return entity;
}

Entity Engine::CreateSprite(string name, string pathToTexture, SpritePivot pivot, SpritePivot anchor, u32 parent)
{
    Entity entity = CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_SPRITE | COMPONENT_TRANSFORM);
    SetLocalPosition(entity, Vec2(0.0f,0.0f));
    SetRotation(entity, 0.0f);

    // TODO: deallocate
    _components.sprites[entity].texture = new OpenglTexture2D(pathToTexture);
    _components.sprites[entity].texture->Load();
    _components.sprites[entity].texture->RendererAllocate();\

    _components.sprites[entity].width = _components.sprites[entity].texture->GetWidth();
    _components.sprites[entity].height = _components.sprites[entity].texture->GetHeight();
    SetScale(entity, Vec2(1.0f,1.0f));

    _components.sprites[entity].pivot = pivot;
    _components.sprites[entity].anchor = anchor;
    _components.sprites[entity].parent = parent;

    return entity;
}
