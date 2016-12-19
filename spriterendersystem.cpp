#include "spriterendersystem.h"

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

#define SPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE)

void SpriteRenderSystem::Update()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & SPRITE_MASK) == SPRITE_MASK)
        {
            glEnable (GL_TEXTURE_2D);
            GLuint handle = ((OpenglTexture2D*)_components->sprites[entity].texture)->GetHandle();
            glBindTexture(GL_TEXTURE_2D, handle);

            glBegin(GL_QUADS);
            glTexCoord2f (0.0f,0.0f);
            glVertex2d(_components->transforms[entity].position.x-0.5, _components->transforms[entity].position.y+0.5);
            glTexCoord2f (1.0f,0.0f);
            glVertex2d(_components->transforms[entity].position.x+0.5, _components->transforms[entity].position.y+0.5);
            glTexCoord2f (1.0f,1.0f);
            glVertex2d(_components->transforms[entity].position.x+0.5, _components->transforms[entity].position.y-0.5);
            glTexCoord2f (0.0f,1.0f);
            glVertex2d(_components->transforms[entity].position.x-0.5, _components->transforms[entity].position.y-0.5);
            glEnd();
        }
    }
}
