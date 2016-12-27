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

void CollisionSystem::Update()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & COLLISION_MASK) == COLLISION_MASK)
        {
            for(u32 entity2 = entity+1; entity2 < MAX_ENTITIES; entity2++)
            {
                if((_components->masks[entity2] & COLLISION_MASK) == COLLISION_MASK)
                {
                    SpriteComponent *sprite = &(_components->sprites[entity]);
                    TransformComponent * transform = &(_components->transforms[entity]);

                    SpriteComponent *sprite2 = &(_components->sprites[entity2]);
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
                        h + y > y2) {
                         //printf("collision entity %d and %d\n", entity, entity2);
                         if(_components->colliders[entity].collisionCallback != nullptr)
                         {
                            _components->colliders[entity].collisionCallback(entity, entity2, _components->colliders[entity].userData);
                         }
                         if(_components->colliders[entity2].collisionCallback != nullptr)
                         {
                            _components->colliders[entity2].collisionCallback(entity2, entity, _components->colliders[entity2].userData);
                         }
                    }
                }
            }
        }
    }
}
