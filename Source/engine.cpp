#include "engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{
    if(_initialized)
    {
        for (std::map<string, Texture2D*>::iterator it=_textureCache.begin(); it!=_textureCache.end(); ++it)
        {
            printf("texture deleted\n");
            delete it->second;
        }
        delete _renderer;
    }
}

Texture2D* Engine::GetTexture(string path)
{
    auto it = _textureCache.find(path);
    if (it != _textureCache.end())
    {
        return it->second;
    }
    else
    {
        Texture2D *ret = _renderer->CreateTexture();
        ret->Load(path);
        ret->RendererAllocate();
        printf("Created texture %s\n", path.c_str());
        _textureCache.insert(std::pair<string, Texture2D*>(path, ret));
        return ret;
    }
}

void Engine::Init(u32 screenWidth, u32 screenHeight)
{
    _renderer = new OpenglRenderer(screenWidth, screenHeight);
    _renderer->Initialize();

    _spriteRenderSystem.Init(&_components, _renderer);
    _textRenderSystem.Init(&_components, _renderer);
    _transformSystem.Init(&_components, _renderer);
    _physicsSystem.Init(&_components, &_transformSystem);
    _collisionSystem.Init(&_components);
    _initialized = true;
}

void Engine::SetScreenSize(IVec2 size)
{
    _renderer->Rescale(size);
    _transformSystem.AllDirty();
}

void Engine::Update(r32 dt)
{
    u32 numActiveEntities = 0;
    u32 activeEntities[MAX_ENTITIES];
    for(u32 i = 0; i < _components._entityPtr; i++)
    {
        if((_components.names[i].flags & COREFLAG_ACTIVE) != 0)
            activeEntities[numActiveEntities++] = i;
    }

    _physicsSystem.Update(dt);
    _transformSystem.UpdateDirtyMatrices();
    _textRenderSystem.Render(activeEntities, numActiveEntities);
    _spriteRenderSystem.Update(activeEntities, numActiveEntities, dt);
    _collisionSystem.Update(activeEntities, numActiveEntities);

    _renderer->RenderGame();
    _renderer->RenderUI();
    _renderer->Flush();
}

Renderer* Engine::GetRenderer()
{
    return _renderer;
}

Entity Engine::CreateScreenEntity(string name, RectPivot pivot, RectPivot anchor, u32 parent)
{
    Entity entity = _components.CreateEntity(name);

    _components.masks[entity] |= ( COMPONENT_TRANSFORM | COMPONENT_RECTTRANSFORM);
    _transformSystem.SetLocalPosition(entity, Vec2(0.0f,0.0f));
    _transformSystem.SetRotation(entity, 0.0f);
    _transformSystem.SetScale(entity, Vec2(1.0f,1.0f));
    _components.recttransforms[entity].pivot = pivot;
    _components.recttransforms[entity].anchor = anchor;
    _components.recttransforms[entity].size = Vec2(1.0f,1.0f);
    _components.transforms[entity].parent = parent;

    return entity;
}

Entity Engine::CreateUISprite(string name, string pathToTexture, RectPivot pivot, RectPivot anchor, u32 parent)
{
    Entity entity = CreateScreenEntity(name, pivot, anchor, parent);

    _components.masks[entity] |= COMPONENT_SPRITE;
    _components.sprites[entity].texture = GetTexture(pathToTexture);
    u32 w = _components.sprites[entity].texture->GetWidth();
    u32 h = _components.sprites[entity].texture->GetHeight();
    _components.sprites[entity].width = w;
    _components.sprites[entity].height = h;
    _components.sprites[entity].pivot = pivot;
    _components.recttransforms[entity].size.x = (r32)w/(r32)h;
    _components.recttransforms[entity].size.y = 1.0f;

    return entity;
}

Entity Engine::CreateUIText(string name, string text, r32 scale, RectPivot pivot, RectPivot anchor, u32 parent)
{
    Entity entity = CreateScreenEntity(name, pivot, anchor, parent);

    _components.masks[entity] |= COMPONENT_TEXT;
    _components.texts[entity].text = text;
    _components.transforms[entity].scale.x = scale;
    _components.transforms[entity].scale.y = scale;

    return entity;
}

Entity Engine::CreateSprite(string name, string pathToTexture, RectPivot pivot)
{
    Entity entity = _components.CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_TRANSFORM);
    _transformSystem.SetLocalPosition(entity, Vec2(0.0f,0.0f));
    _transformSystem.SetRotation(entity, 0.0f);
    _transformSystem.SetScale(entity, Vec2(1.0f,1.0f));

    _components.masks[entity] |= COMPONENT_SPRITE;
    _components.sprites[entity].texture = GetTexture(pathToTexture);
    u32 w = _components.sprites[entity].texture->GetWidth();
    u32 h = _components.sprites[entity].texture->GetHeight();
    _components.sprites[entity].width = w;
    _components.sprites[entity].height = h;
    _components.sprites[entity].pivot = pivot;

    return entity;
}

Entity Engine::CreateAnimatedSprite(string name, string pathToTexture, u32 frames, r32 framesPerSecond, RectPivot pivot)
{
    Entity entity = _components.CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_TRANSFORM);
    _transformSystem.SetLocalPosition(entity, Vec2(0.0f,0.0f));
    _transformSystem.SetRotation(entity, 0.0f);
    _transformSystem.SetScale(entity, Vec2(1.0f,1.0f));

    _components.masks[entity] |= COMPONENT_SPRITE;
    _components.sprites[entity].texture = GetTexture(pathToTexture);
    u32 w = _components.sprites[entity].texture->GetWidth();
    u32 h = _components.sprites[entity].texture->GetHeight();
    _components.sprites[entity].width = w;
    _components.sprites[entity].height = h;
    _components.sprites[entity].pivot = pivot;

    _components.masks[entity] |= COMPONENT_ANIMSPRITE;
    _components.animsprites[entity].frameWidth = w / frames;
    _components.animsprites[entity].framesPerSecond = framesPerSecond;
    _components.animsprites[entity].timer = 0.0f;

    return entity;
}

void Engine::SetGameProjection(Mat4& mat)
{
    _renderer->_gameMatrix = mat;
}


