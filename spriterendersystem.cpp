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

Mat4 getMatrix(Vec2 posv, Vec2 scalev, r32 rot)
{
    Mat4 transM = translate(posv);
    Mat4 scaleM = scale(scalev);
    Mat4 rotM = rotate(rot);
    return transM*rotM*scaleM;
}

Vec2 anchorOffset(SpritePivot parentPivot, SpritePivot anchorPivot)
{
    switch(parentPivot)
    {
        case SPRITEPIVOT_CENTER:
        {
            switch(anchorPivot)
            {
                case SPRITEPIVOT_TOPLEFT:
                    return Vec2(-0.5, 0.5);
                case SPRITEPIVOT_TOPRIGHT:
                    return Vec2(0.5, 0.5);
                case SPRITEPIVOT_BOTTOMLEFT:
                    return Vec2(-0.5, -0.5);
                case SPRITEPIVOT_BOTTOMRIGHT:
                    return Vec2(0.5, -0.5);
                case SPRITEPIVOT_CENTER:
                    return Vec2::Zero();
                default:
                    return Vec2::Zero();
            }
        } break;
        case SPRITEPIVOT_TOPLEFT:
        {
            switch(anchorPivot)
            {
                case SPRITEPIVOT_TOPLEFT:
                    return Vec2(0.0f, 0.0f);
                case SPRITEPIVOT_TOPRIGHT:
                    return Vec2(1.0f, 0.0f);
                case SPRITEPIVOT_BOTTOMLEFT:
                    return Vec2(0.0f, -1.0f);
                case SPRITEPIVOT_BOTTOMRIGHT:
                    return Vec2(1.0f, -1.0f);
                case SPRITEPIVOT_CENTER:
                    return Vec2(0.5f, -0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case SPRITEPIVOT_TOPRIGHT:
        {
            switch(anchorPivot)
            {
                case SPRITEPIVOT_TOPLEFT:
                    return Vec2(-1.0f, 0.0f);
                case SPRITEPIVOT_TOPRIGHT:
                    return Vec2(0.0f, 0.0f);
                case SPRITEPIVOT_BOTTOMLEFT:
                    return Vec2(-1.0f, -1.0f);
                case SPRITEPIVOT_BOTTOMRIGHT:
                    return Vec2(0.0f, -1.0f);
                case SPRITEPIVOT_CENTER:
                    return Vec2(-0.5f, -0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case SPRITEPIVOT_BOTTOMLEFT:
        {
            switch(anchorPivot)
            {
                case SPRITEPIVOT_TOPLEFT:
                    return Vec2(0.0f, 1.0f);
                case SPRITEPIVOT_TOPRIGHT:
                    return Vec2(1.0f, 1.0f);
                case SPRITEPIVOT_BOTTOMLEFT:
                    return Vec2(0.0f, 0.0f);
                case SPRITEPIVOT_BOTTOMRIGHT:
                    return Vec2(1.0f, 0.0f);
                case SPRITEPIVOT_CENTER:
                    return Vec2(0.5f, 0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case SPRITEPIVOT_BOTTOMRIGHT:
        {
            switch(anchorPivot)
            {
                case SPRITEPIVOT_TOPLEFT:
                    return Vec2(-1.0f, 1.0f);
                case SPRITEPIVOT_TOPRIGHT:
                    return Vec2(0.0f, 1.0f);
                case SPRITEPIVOT_BOTTOMLEFT:
                    return Vec2(-1.0f, 0.0f);
                case SPRITEPIVOT_BOTTOMRIGHT:
                    return Vec2(0.0f, 0.0f);
                case SPRITEPIVOT_CENTER:
                    return Vec2(-0.5f, 0.5f);
                default:
                    return Vec2::Zero();
            }

        } break;
    }
    assert(false);
    return Vec2::Zero();
}

inline void mat4Vec2Mul(Vec2 *d, Mat4 *m, Vec2 *v)
{
    d->x = v->x*m->m11+v->y*m->m12+m->m14;
    d->y = v->x*m->m21+v->y*m->m22+m->m24;
}

Vec2 SpriteRenderSystem::GetAnchor(i32 entity, SpritePivot pivot)
{
    Vec2 scale;
    Vec2 offset;

    if(entity == -1) // screen
    {
        scale = Vec2(4.0f*1.333f,4.0f);
        offset = anchorOffset(SPRITEPIVOT_BOTTOMLEFT, pivot);
        return scale * offset;
    }
    else // some other entity
    {
        scale = _components->transforms[entity].scale;
        offset = anchorOffset(_components->sprites[entity].pivot, pivot);
        return scale*offset;
    }
}

void SpriteRenderSystem::Update()
{
    _components->transforms[0].rotation += 0.001;

    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & SPRITE_MASK) == SPRITE_MASK)
        {
            SpriteComponent* sprite = &_components->sprites[entity];
            r32 spriteAspect = (r32)sprite->width/(r32)sprite->height;
            TransformComponent* transform = &_components->transforms[entity];

            Vec2 anchor = GetAnchor(sprite->parent, sprite->anchor);
            transform->position = anchor + transform->localPosition;

            transform->modelMatrix = getMatrix(transform->position, transform->scale, transform->rotation);
            if(sprite->parent != -1)
            {
                transform->modelMatrix = _components->transforms[sprite->parent].modelMatrix*transform->modelMatrix;
            }
            Mat4 projM = ortho(0.0f, 4.0f*1.33333f, 0.0f, 4.0f);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf((GLfloat*)&projM);
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((GLfloat*)&transform->modelMatrix);

            glEnable (GL_TEXTURE_2D);
            GLuint handle = ((OpenglTexture2D*)sprite->texture)->GetHandle();
            glBindTexture(GL_TEXTURE_2D, handle);

            glBegin(GL_QUADS);
            switch(sprite->pivot)
            {
                case SPRITEPIVOT_CENTER:
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
                case SPRITEPIVOT_TOPLEFT:
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
                case SPRITEPIVOT_TOPRIGHT:
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
                case SPRITEPIVOT_BOTTOMLEFT:
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
                case SPRITEPIVOT_BOTTOMRIGHT:
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
