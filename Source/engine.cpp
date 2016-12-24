#include "engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{
    if(_initialized)
    {
        for(u32 e = 0; e < MAX_ENTITIES; e++)
        {
            // FREE textures
            if((_components.masks[e] & COMPONENT_SPRITE) == COMPONENT_SPRITE)
            {
                delete _components.sprites[e].texture;
            }
        }
        delete _renderer;
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
    printf("engine init");

    //Entity sprite1 =_engine.CreateSprite("sprite", "forwardp.jpg", RECTPIVOT_CENTER, RECTPIVOT_CENTER);

    //Entity sprite3 = CreateSprite("sprite3", "test.png", RECTPIVOT_CENTER, RECTPIVOT_CENTER);
    //Entity sprite2 = CreateSprite("sprite2", "forwardp.jpg", RECTPIVOT_CENTER, RECTPIVOT_TOPLEFT, sprite3);
    //Entity text1 = CreateText("text1", "Just testing!", 1.0f, RECTPIVOT_BOTTOMLEFT, RECTPIVOT_BOTTOMRIGHT, sprite3);
    //_transformSystem.SetLocalPosition(text1, Vec2(0.0f,-0.0f));
    //_transformSystem.SetScale(sprite3, Vec2(100.0f,100.0f));
    //_transformSystem.SetScale(sprite2, Vec2(1.0f,1.0f));

    _initialized = true;
}

void Engine::SetScreenSize(IVec2 size)
{
    printf("rescale \n");
    _renderer->Rescale(size);
    _transformSystem.AllDirty();
}

void Engine::Update(r32 dt)
{
    //_transformSystem.Rotate(0,0.2f*dt);
    //_transformSystem.Rotate(1,2.f*dt);
    //_transformSystem.Rotate(1,0.02f*dt);
    //_transformSystem.Rotate(2,0.010f*dt);
    _physicsSystem.Update(dt);
    _transformSystem.UpdateDirtyMatrices();
    _spriteRenderSystem.Update();
    _textRenderSystem.Render();

    _renderer->RenderGame();
    _renderer->RenderUI();
}

Renderer* Engine::GetRenderer()
{
    return _renderer;
}

Entity Engine::CreateEntity(string name)
{
    Entity entity = _entityPtr++;
    _components.masks[entity] = COMPONENT_NONE;
    _components.names[entity].name.assign(name);
    return entity;
}

Entity Engine::CreateScreenEntity(string name, RectPivot pivot, RectPivot anchor, u32 parent)
{
    Entity entity = CreateEntity(name);

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
    _components.sprites[entity].texture = new OpenglTexture2D(pathToTexture);
    _components.sprites[entity].texture->Load();
    _components.sprites[entity].texture->RendererAllocate();\
    r32 w = _components.sprites[entity].texture->GetWidth();
    r32 h = _components.sprites[entity].texture->GetHeight();
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
    Entity entity = CreateEntity(name);
    _components.masks[entity] |= (COMPONENT_TRANSFORM);
    _transformSystem.SetLocalPosition(entity, Vec2(0.0f,0.0f));
    _transformSystem.SetRotation(entity, 0.0f);
    _transformSystem.SetScale(entity, Vec2(1.0f,1.0f));

    _components.masks[entity] |= COMPONENT_SPRITE;
    _components.sprites[entity].texture = new OpenglTexture2D(pathToTexture);
    _components.sprites[entity].texture->Load();
    _components.sprites[entity].texture->RendererAllocate();\
    r32 w = _components.sprites[entity].texture->GetWidth();
    r32 h = _components.sprites[entity].texture->GetHeight();
    _components.sprites[entity].width = w;
    _components.sprites[entity].height = h;
    _components.sprites[entity].pivot = pivot;

    return entity;
}

void Engine::SetGameProjection(Mat4& mat)
{
    _renderer->_gameMatrix = mat;
}


