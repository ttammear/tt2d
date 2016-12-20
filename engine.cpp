#include "engine.h"

Engine::Engine()
{
    _spriteRenderSystem.Init(&_components, &_renderer);
    _transformSystem.Init(&_components);
}

Engine::~Engine()
{
    for(u32 e = 0; e < MAX_ENTITIES; e++)
    {
        // FREE textures
        if((_components.masks[e] & COMPONENT_SPRITE) == COMPONENT_SPRITE)
        {
            delete _components.sprites[e].texture;
        }
    }
}

void Engine::Update(r32 dt)
{
    _transformSystem.UpdateDirtyMatrices();
    _spriteRenderSystem.Update();
}

Entity Engine::CreateEntity(string name)
{
    Entity entity = _entityPtr++;
    _components.masks[entity] = COMPONENT_NONE;
    return entity;
}

Entity Engine::CreateSprite(string name, string pathToTexture, RectPivot pivot, RectPivot anchor, u32 parent)
{
    Entity entity = CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_SPRITE | COMPONENT_TRANSFORM | COMPONENT_RECTTRANSFORM);
    _transformSystem.SetLocalPosition(entity, Vec2(0.0f,0.0f));
    _transformSystem.SetRotation(entity, 0.0f);

    _components.sprites[entity].texture = new OpenglTexture2D(pathToTexture);
    _components.sprites[entity].texture->Load();
    _components.sprites[entity].texture->RendererAllocate();\

    _components.sprites[entity].width = _components.sprites[entity].texture->GetWidth();
    _components.sprites[entity].height = _components.sprites[entity].texture->GetHeight();
    _transformSystem.SetScale(entity, Vec2(1.0f,1.0f));

    _components.recttransforms[entity].pivot = pivot;
    _components.recttransforms[entity].anchor = anchor;
    _components.transforms[entity].parent = parent;

    return entity;
}
