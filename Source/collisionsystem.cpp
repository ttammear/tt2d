#include "collisionsystem.h"

#define COLLISION_MASK (COMPONENT_TRANSFORM | COMPONENT_SPRITE | COMPONENT_COLLIDER)

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::Init(ComponentManager *components)
{
    _components = components;
}

void CollisionSystem::AddCollider(u32 entity)
{
    _components->masks[entity] |= COMPONENT_COLLIDER;
}

void CollisionSystem::SetCallback(u32 entity, CollisionCallback_t* callback, void* userData)
{
    _components->colliders[entity].collisionCallback = callback;
    _components->colliders[entity].userData = userData;
}

void CollisionSystem::Update(u32 entities[], u32 entityCount)
{
    // TODO: pair culling
    // quadtrees for example
    struct Pair
    {
        u16 first;
        u16 second;
    };

    Pair pairs[(MAX_ENTITIES*MAX_ENTITIES)/4]; // TODO: can overflow
    u32 pairCount = 0;

    for(u32 i = 0; i < entityCount; i++)
    {
        u32 entity = entities[i];
        if((_components->masks[entity] & COLLISION_MASK) == COLLISION_MASK)
        {
            for(u32 j = i+1; j < entityCount; j++)
            {
                u32 entity2 = entities[j];
                if((_components->masks[entity2] & COLLISION_MASK) == COLLISION_MASK)
                {
                    TransformComponent * transform = &(_components->transforms[entity]);
                    TransformComponent * transform2 = &(_components->transforms[entity2]);

                    r32 x, y, w, h;
                    x = transform->localPosition.x - 0.5f * transform->scale.x;
                    y = transform->localPosition.y - 0.5f * transform->scale.y;
                    w = transform->scale.x;
                    h = transform->scale.y;

                    r32 x2, y2, w2, h2;
                    x2 = transform2->localPosition.x - 0.5f * transform2->scale.x;
                    y2 = transform2->localPosition.y - 0.5f * transform2->scale.y;
                    w2 = transform2->scale.x;
                    h2 = transform2->scale.y;

                    if (x < x2 + w2 &&
                        x + w > x2 &&
                        y < y2 + h2 &&
                        h + y > y2)
                    {
                        pairs[pairCount].first = entity;
                        pairs[pairCount].second = entity2;
                        pairCount++;
                    }
                }
            }
        }
    }

    for(i32 pairIndex = pairCount-1; pairIndex >= 0; pairIndex--)
    {
        u32 first = pairs[pairIndex].first;
        u32 second = pairs[pairIndex].second;
        if(_components->colliders[first].collisionCallback == nullptr)
        {}
        else
        {
           _components->colliders[first].collisionCallback(first, second, _components->colliders[first].userData);
        }
        if(_components->colliders[second].collisionCallback == nullptr)
        {}
        else
        {
           _components->colliders[second].collisionCallback(second, first, _components->colliders[second].userData);
        }
    }
}
