#include "spriterendersystem.h"

#define UISPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE)
#define ANIMATEDSPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE | COMPONENT_ANIMSPRITE)

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

void SpriteRenderSystem::Update(u32 entities[], u32 numEntities, r32 dt)
{  
    for(u32 i = 0; i < numEntities; i++)
    {
        u32 entity = entities[i];
        if((_components->masks[entity] & UISPRITE_MASK) == UISPRITE_MASK)
        {
            bool ui = (_components->masks[entity] & COMPONENT_RECTTRANSFORM) == COMPONENT_RECTTRANSFORM;
            bool animated = (_components->masks[entity] & COMPONENT_ANIMSPRITE) != 0;
            bool render = true;

            SpriteComponent* sprite = &_components->sprites[entity];
            r32 spriteAspect = animated ? 1.0f : (r32)sprite->width/(r32)sprite->height;
            TransformComponent* transform = &_components->transforms[entity];

            u32 textureHandle = ((OpenglTexture2D*)sprite->texture)->GetHandle();
            Rect rect;
            rect.width = 1.0f*spriteAspect;
            rect.height = 1.0f;

            switch(sprite->pivot)
            {
                case RECTPIVOT_CENTER:
                {
                    rect.x = -0.5f*spriteAspect;
                    rect.y = -0.5f;
                } break;
                case RECTPIVOT_TOPLEFT:
                {
                    rect.x = 0.0f;
                    rect.y = -1.0f;
                } break;
                case RECTPIVOT_TOPRIGHT:
                {
                    rect.x = -1.0f*spriteAspect;
                    rect.y = -1.0f;
                } break;
                case RECTPIVOT_BOTTOMLEFT:
                {
                    rect.x = -0.0f;
                    rect.y = -0.0f;
                } break;
                case RECTPIVOT_BOTTOMRIGHT:
                {
                    rect.x = -1.0f*spriteAspect;
                    rect.y = -0.0f;
                } break;
            }

            Rect texRect;

            // not animated
            if(!animated)
            {
                texRect = Rect(0.0f, 0.0f, 1.0f, 1.0f);
            }
            // animated
            else
            {
                AnimatedSpriteComponent* asc = &_components->animsprites[entity];
                u32 frames = sprite->width / asc->frameWidth;
                r32 frameTime = 1.0f / asc->framesPerSecond;
                r32 animLength = frames*frameTime;
                r32 curTime = fmod(asc->timer, animLength);
                u32 frame = (u32)(curTime / frameTime);
                assert(frame >= 0 && frame < frames);
                r32 coordWidth = 1.0f/frames;
                texRect = Rect(coordWidth*(r32)frame, 0.0f, coordWidth, 1.0f);
                if(asc->oneShot && asc->timer > animLength)
                {
                    render = false;
                    _components->DeleteEntity(entity);
                }
                asc->timer += dt;
            }
            if(render)
                _renderer->PushTexturedQuadRenderCommand(rect, texRect, transform->modelMatrix, textureHandle, ui);
        }
    }
}
