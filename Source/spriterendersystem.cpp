#include "spriterendersystem.h"

#define UISPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE)
#define SPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE)

SpriteRenderSystem::SpriteRenderSystem()
{

}

SpriteRenderSystem::SpriteRenderSystem(ComponentManager* components)
{
    _components = components;
}

void SpriteRenderSystem::Init(ComponentManager* components, Renderer* renderer)
{
    _components = components;
    _renderer = renderer;
}

void SpriteRenderSystem::Update()
{  
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & UISPRITE_MASK) == UISPRITE_MASK)
        {
            bool ui = (_components->masks[entity] & COMPONENT_RECTTRANSFORM) == COMPONENT_RECTTRANSFORM;
            SpriteComponent* sprite = &_components->sprites[entity];
            r32 spriteAspect = (r32)sprite->width/(r32)sprite->height;
            TransformComponent* transform = &_components->transforms[entity];

            u32 textureHandle = ((OpenglTexture2D*)sprite->texture)->GetHandle();
            Vec2 topleft;
            Vec2 bottomright;
            switch(sprite->pivot)
            {
                case RECTPIVOT_CENTER:
                {
                    topleft = Vec2(-0.5*spriteAspect, 0.5);
                    bottomright = Vec2(0.5*spriteAspect, -0.5);
                } break;
                case RECTPIVOT_TOPLEFT:
                {
                    topleft = Vec2(0.0f, 0.0f);
                    bottomright = Vec2(1.0f*spriteAspect, -1.0f);
                } break;
                case RECTPIVOT_TOPRIGHT:
                {
                    topleft = Vec2(-1.0f*spriteAspect, 0.0f);
                    bottomright = Vec2(0.0f, -1.0f);
                } break;
                case RECTPIVOT_BOTTOMLEFT:
                {
                    topleft = Vec2(0.0f, 1.0f);
                    bottomright = Vec2(1.0f*spriteAspect, 0.0f);
                } break;
                case RECTPIVOT_BOTTOMRIGHT:
                {
                    topleft = Vec2(-1.0f*spriteAspect, 1.0f);
                    bottomright = Vec2(0.0f, 0.0f);
                } break;
            }
            _renderer->PushTexturedQuadRenderCommand(topleft, bottomright, transform->modelMatrix, textureHandle, ui);
        }
    }
}
