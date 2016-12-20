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

Vec2 anchorOffset2(RectPivot parentPivot, RectPivot anchorPivot)
{
    switch(parentPivot)
    {
        case RECTPIVOT_CENTER:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    return Vec2(-0.5, 0.5);
                case RECTPIVOT_TOPRIGHT:
                    return Vec2(0.5, 0.5);
                case RECTPIVOT_BOTTOMLEFT:
                    return Vec2(-0.5, -0.5);
                case RECTPIVOT_BOTTOMRIGHT:
                    return Vec2(0.5, -0.5);
                case RECTPIVOT_CENTER:
                    return Vec2::Zero();
                default:
                    return Vec2::Zero();
            }
        } break;
        case RECTPIVOT_TOPLEFT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    return Vec2(0.0f, 0.0f);
                case RECTPIVOT_TOPRIGHT:
                    return Vec2(1.0f, 0.0f);
                case RECTPIVOT_BOTTOMLEFT:
                    return Vec2(0.0f, -1.0f);
                case RECTPIVOT_BOTTOMRIGHT:
                    return Vec2(1.0f, -1.0f);
                case RECTPIVOT_CENTER:
                    return Vec2(0.5f, -0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case RECTPIVOT_TOPRIGHT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    return Vec2(-1.0f, 0.0f);
                case RECTPIVOT_TOPRIGHT:
                    return Vec2(0.0f, 0.0f);
                case RECTPIVOT_BOTTOMLEFT:
                    return Vec2(-1.0f, -1.0f);
                case RECTPIVOT_BOTTOMRIGHT:
                    return Vec2(0.0f, -1.0f);
                case RECTPIVOT_CENTER:
                    return Vec2(-0.5f, -0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case RECTPIVOT_BOTTOMLEFT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    return Vec2(0.0f, 1.0f);
                case RECTPIVOT_TOPRIGHT:
                    return Vec2(1.0f, 1.0f);
                case RECTPIVOT_BOTTOMLEFT:
                    return Vec2(0.0f, 0.0f);
                case RECTPIVOT_BOTTOMRIGHT:
                    return Vec2(1.0f, 0.0f);
                case RECTPIVOT_CENTER:
                    return Vec2(0.5f, 0.5f);
                default:
                    return Vec2::Zero();
            }
        } break;
        case RECTPIVOT_BOTTOMRIGHT:
        {
            switch(anchorPivot)
            {
                case RECTPIVOT_TOPLEFT:
                    return Vec2(-1.0f, 1.0f);
                case RECTPIVOT_TOPRIGHT:
                    return Vec2(0.0f, 1.0f);
                case RECTPIVOT_BOTTOMLEFT:
                    return Vec2(-1.0f, 0.0f);
                case RECTPIVOT_BOTTOMRIGHT:
                    return Vec2(0.0f, 0.0f);
                case RECTPIVOT_CENTER:
                    return Vec2(-0.5f, 0.5f);
                default:
                    return Vec2::Zero();
            }

        } break;
    }
    assert(false);
    return Vec2::Zero();
}

Vec2 TransformSystem::GetAnchor(i32 entity, RectPivot pivot)
{
    Vec2 scale;
    Vec2 offset;

    if(entity == -1) // screen
    {
        scale = Vec2(4.0f*1.333f,4.0f);
        offset = anchorOffset2(RECTPIVOT_BOTTOMLEFT, pivot);
        return scale * offset;
    }
    else // some other entity
    {
        scale = _components->transforms[entity].scale;
        offset = anchorOffset2(_components->recttransforms[entity].pivot, pivot);
        return scale*offset;
    }
}

void TransformSystem::Init(ComponentManager* components)
{
    _components = components;
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
    for(u32 e = 0; e < MAX_ENTITIES; e++)
    {
        if(_components->transforms[e].parent == entity)
        {
            _components->transforms[e].dirty = true;
            SetDirty(e);
        }
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
                    TransformComponent* transform = &_components->transforms[entity];
                    RectTransformComponent* rtransform = &_components->recttransforms[entity];
                    Vec2 anchor = GetAnchor(transform->parent, rtransform->anchor);
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
                    assert(false);
                }
            }
        }
    }
}
