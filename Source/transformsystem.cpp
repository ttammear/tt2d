#include "transformsystem.h"

#define TRANSFORM_MASK (COMPONENT_TRANSFORM)
#define RECTTRANSFORM_MASK (COMPONENT_RECTTRANSFORM)

TransformSystem::TransformSystem()
{

}

Mat4 getMatrix2(Vec2 posv, Vec2 scalev, r32 rot)
{
    Mat4 transM = translate(posv);
    Mat4 scaleM = scale(scalev);
    Mat4 rotM = rotate(rot);
    return transM*rotM*scaleM;
}

Vec2 anchorOffset2(RectPivot parentPivot, RectPivot anchorPivot, Vec2 size)
{
    Vec2 ret;

    switch(parentPivot)
    {
        case RECTPIVOT_CENTER:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    ret = Vec2(-0.5, 0.5);
                    goto end;
                case RECTPIVOT_TOPRIGHT:
                    ret = Vec2(0.5, 0.5);
                    goto end;
                case RECTPIVOT_BOTTOMLEFT:
                    ret = Vec2(-0.5, -0.5);
                    goto end;
                case RECTPIVOT_BOTTOMRIGHT:
                    ret = Vec2(0.5, -0.5);
                    goto end;
                case RECTPIVOT_CENTER:
                    ret = Vec2::Zero();
                    goto end;
                default:
                    ret = Vec2::Zero();
                    goto end;
            }
        } break;
        case RECTPIVOT_TOPLEFT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    ret = Vec2(0.0f, 0.0f);
                    goto end;
                case RECTPIVOT_TOPRIGHT:
                    ret = Vec2(1.0f, 0.0f);
                    goto end;
                case RECTPIVOT_BOTTOMLEFT:
                    ret = Vec2(0.0f, -1.0f);
                    goto end;
                case RECTPIVOT_BOTTOMRIGHT:
                    ret = Vec2(1.0f, -1.0f);
                    goto end;
                case RECTPIVOT_CENTER:
                    ret = Vec2(0.5f, -0.5f);
                    goto end;
                default:
                    ret = Vec2::Zero();
                    goto end;
            }
        } break;
        case RECTPIVOT_TOPRIGHT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    ret = Vec2(-1.0f, 0.0f);
                    goto end;
                case RECTPIVOT_TOPRIGHT:
                    ret = Vec2(0.0f, 0.0f);
                    goto end;
                case RECTPIVOT_BOTTOMLEFT:
                    ret = Vec2(-1.0f, -1.0f);
                    goto end;
                case RECTPIVOT_BOTTOMRIGHT:
                    ret = Vec2(0.0f, -1.0f);
                    goto end;
                case RECTPIVOT_CENTER:
                    ret = Vec2(-0.5f, -0.5f);
                    goto end;
                default:
                    ret = Vec2::Zero();
                    goto end;
            }
        } break;
        case RECTPIVOT_BOTTOMLEFT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    ret = Vec2(0.0f, 1.0f);
                    goto end;
                case RECTPIVOT_TOPRIGHT:
                    ret = Vec2(1.0f, 1.0f);
                    goto end;
                case RECTPIVOT_BOTTOMLEFT:
                    ret = Vec2(0.0f, 0.0f);
                    goto end;
                case RECTPIVOT_BOTTOMRIGHT:
                    ret = Vec2(1.0f, 0.0f);
                    goto end;
                case RECTPIVOT_CENTER:
                    ret = Vec2(0.5f, 0.5f);
                    goto end;
                default:
                    ret = Vec2::Zero();
                    goto end;
            }
        } break;
        case RECTPIVOT_BOTTOMRIGHT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    ret = Vec2(-1.0f, 1.0f);
                    goto end;
                case RECTPIVOT_TOPRIGHT:
                    ret = Vec2(0.0f, 1.0f);
                    goto end;
                case RECTPIVOT_BOTTOMLEFT:
                    ret = Vec2(-1.0f, 0.0f);
                    goto end;
                case RECTPIVOT_BOTTOMRIGHT:
                    ret = Vec2(0.0f, 0.0f);
                    goto end;
                case RECTPIVOT_CENTER:
                    ret = Vec2(-0.5f, 0.5f);
                    goto end;
                default:
                    ret = Vec2::Zero();
                    goto end;
            }

        } break;
    }
    end:
    return ret*size;
}

Vec2 TransformSystem::GetAnchor(i32 entity, RectPivot pivot)
{
    Vec2 scale;
    Vec2 offset;

    if(entity == -1) // screen
    {
        scale = _renderer->GetScreenSize();
        offset = anchorOffset2(RECTPIVOT_BOTTOMLEFT, pivot, Vec2(1.0f,1.0f));
        return scale * offset;
    }
    else // some other entity
    {
        scale = Vec2(1.0f,1.0f);
        offset = anchorOffset2(_components->recttransforms[entity].pivot, pivot, _components->recttransforms[entity].size);
        return scale * offset;
    }
}

void TransformSystem::Init(ComponentManager *components, Renderer *renderer)
{
    _components = components;
    _renderer = renderer;
}

void TransformSystem::SetLocalPosition(u32 entity, Vec2 position)
{
    _components->transforms[entity].dirty = true;
    _components->transforms[entity].localPosition = position;
}

void TransformSystem::SetDirty(u32 entity)
{
    _components->transforms[entity].dirty = true;
    // TODO: make better hierarchy tree system
    for(i32 e = 0; e < MAX_ENTITIES; e++)
    {
        if(_components->transforms[e].parent == (i32)entity)
        {
            _components->transforms[e].dirty = true;
            SetDirty(e);
        }
    }
}

void TransformSystem::AllDirty()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        _components->transforms[entity].dirty = true;
    }
}

void TransformSystem::SetScale(u32 entity, Vec2 scale)
{
    SetDirty(entity);
    _components->transforms[entity].scale = scale;
}

void TransformSystem::Rotate(u32 entity, r32 rotation)
{
    SetDirty(entity);
    _components->transforms[entity].rotation += rotation;
}

void TransformSystem::SetRotation(u32 entity, r32 rotation)
{
    SetDirty(entity);
    _components->transforms[entity].rotation = rotation;
}

void TransformSystem::UpdateDirtyMatrices()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & TRANSFORM_MASK) == TRANSFORM_MASK)
        {
            if(_components->transforms[entity].dirty)
            {
                if((_components->masks[entity] & RECTTRANSFORM_MASK))
                {
                    TransformComponent* transform = &(_components->transforms[entity]);
                    RectTransformComponent* rtransform = &(_components->recttransforms[entity]);
                    Vec2 anchor = GetAnchor(transform->parent, rtransform->anchor);
                    printf("anchor %d %s %f %f\n", transform->parent,_components->names[entity].name.c_str(),anchor.x, anchor.y);
                    transform->position = anchor + transform->localPosition;

                    transform->modelMatrix = getMatrix2(transform->position, transform->scale, transform->rotation);
                    if(transform->parent != -1)
                    {
                        transform->modelMatrix = _components->transforms[transform->parent].modelMatrix*transform->modelMatrix;
                    }
                    transform->dirty = false;
                }
                else
                {
                    TransformComponent* transform = &(_components->transforms[entity]);
                    transform->position = transform->localPosition;

                    transform->modelMatrix = getMatrix2(transform->position, transform->scale, transform->rotation);
                    if(transform->parent != -1)
                    {
                        transform->modelMatrix = _components->transforms[transform->parent].modelMatrix*transform->modelMatrix;
                    }
                    transform->dirty = false;
                }
            }
        }
    }
}
