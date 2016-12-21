#include "spriterendersystem.h"

#define SPRITE_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE | COMPONENT_RECTTRANSFORM)

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
        if((_components->masks[entity] & SPRITE_MASK) == SPRITE_MASK)
        {
            SpriteComponent* sprite = &_components->sprites[entity];
            r32 spriteAspect = (r32)sprite->width/(r32)sprite->height;
            TransformComponent* transform = &_components->transforms[entity];

            Mat4 projM = ortho(0.0f, 4.0f*1.33333f, 0.0f, 4.0f);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf((GLfloat*)&projM);
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((GLfloat*)&transform->modelMatrix);

            glEnable (GL_TEXTURE_2D);
            GLuint handle = ((OpenglTexture2D*)sprite->texture)->GetHandle();
            glBindTexture(GL_TEXTURE_2D, handle);

            glBegin(GL_QUADS);
            switch(_components->recttransforms[entity].pivot)
            {
                case RECTPIVOT_CENTER:
                {
                    glTexCoord2f (0.0f,0.0f);
                    glVertex2d(-0.5*spriteAspect, 0.5);
                    glTexCoord2f (1.0f,0.0f);
                    glVertex2d(0.5*spriteAspect, 0.5);
                    glTexCoord2f (1.0f,1.0f);
                    glVertex2d(0.5*spriteAspect, -0.5);
                    glTexCoord2f (0.0f,1.0f);
                    glVertex2d(-0.5*spriteAspect, -0.5);
                } break;
                case RECTPIVOT_TOPLEFT:
                {
                    glTexCoord2f (0.0f,0.0f);
                    glVertex2d(0.0f, 0.0f);
                    glTexCoord2f (1.0f,0.0f);
                    glVertex2d(1.0f*spriteAspect, 0.0f);
                    glTexCoord2f (1.0f,1.0f);
                    glVertex2d(1.0f*spriteAspect, -1.0f);
                    glTexCoord2f (0.0f,1.0f);
                    glVertex2d(0.0f, -1.0f);
                } break;
                case RECTPIVOT_TOPRIGHT:
                {
                    glTexCoord2f (0.0f,0.0f);
                    glVertex2d(-1.0f*spriteAspect, 0.0f);
                    glTexCoord2f (1.0f,0.0f);
                    glVertex2d(0.0f, 0.0f);
                    glTexCoord2f (1.0f,1.0f);
                    glVertex2d(0.0f, -1.0f);
                    glTexCoord2f (0.0f,1.0f);
                    glVertex2d(-1.0f*spriteAspect, -1.0f);
                } break;
                case RECTPIVOT_BOTTOMLEFT:
                {
                    glTexCoord2f (0.0f,0.0f);
                    glVertex2d(0.0f, 1.0f);
                    glTexCoord2f (1.0f,0.0f);
                    glVertex2d(1.0f*spriteAspect, 1.0f);
                    glTexCoord2f (1.0f,1.0f);
                    glVertex2d(1.0f*spriteAspect, 0.0f);
                    glTexCoord2f (0.0f,1.0f);
                    glVertex2d(0.0f, 0.0f);
                } break;
                case RECTPIVOT_BOTTOMRIGHT:
                {
                    glTexCoord2f (0.0f,0.0f);
                    glVertex2d(-1.0f, 1.0f);
                    glTexCoord2f (1.0f,0.0f);
                    glVertex2d(0.0f, 1.0f);
                    glTexCoord2f (1.0f,1.0f);
                    glVertex2d(0.0f, 0.0f);
                    glTexCoord2f (0.0f,1.0f);
                    glVertex2d(-1.0f, 0.0f);
                } break;
            }
            glEnd();
        }
    }
}
