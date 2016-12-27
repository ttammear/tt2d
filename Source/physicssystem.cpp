
#include "physicssystem.h"

#define PHYSICS_MASK (COMPONENT_TRANSFORM | COMPONENT_PHYSICS)

PhysicsSystem::PhysicsSystem()
{

}

void PhysicsSystem::Init(ComponentManager *components, TransformSystem* transforms)
{
    _components = components;
    _transforms = transforms;
}

void PhysicsSystem::Update(r32 dt)
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & PHYSICS_MASK) == PHYSICS_MASK)
        {
            PhysicsComponent* phys = &_components->physics[entity];
            _components->transforms[entity].localPosition += phys->velocity*dt;
            _transforms->SetDirty(entity);
            printf("physics update\n");
        }
    }
}

void PhysicsSystem::SetVelocity(u32 entity, Vec2 vel)
{
    // TODO: remove this hack
    _components->masks[entity] |= COMPONENT_PHYSICS;
    _components->physics[entity].velocity = vel;
}

#include <math.h>

void PhysicsSystem::AddForwardVelocity(u32 entity, r32 scale)
{
    // TODO: remove this hack
    _components->masks[entity] |= COMPONENT_PHYSICS;

    r32 angle = _components->transforms[entity].rotation;

    Vec2 unitForw = Vec2(sin(-angle), cos(angle));
    _components->physics[entity].velocity += unitForw*scale;
}
