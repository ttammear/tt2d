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

void Engine::SetPosition(Entity entity, Vec2 position)
{
    _components.transforms[entity].position = position;
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

Entity Engine::CreateSprite(string name, string pathToTexture)
{
    Entity entity = CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_SPRITE | COMPONENT_TRANSFORM);
    SetPosition(entity, Vec2::Zero());
    SetRotation(entity, 0.0f);

    // TODO: deallocate
    _components.sprites[entity].texture = new OpenglTexture2D(pathToTexture);
    _components.sprites[entity].texture->Load();
    _components.sprites[entity].texture->RendererAllocate();

    return entity;
}
