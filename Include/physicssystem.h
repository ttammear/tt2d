#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "componentmanager.h"
#include "transformsystem.h"

class PhysicsSystem
{
public:
    PhysicsSystem();
    void Init(ComponentManager* components, TransformSystem* transforms);
    void Update(r32 dt);
    void SetVelocity(u32 entity, Vec2 vel);
    void AddForwardVelocity(u32 entity, r32 scale);
    void SetDrag(u32 entity, r32 drag);
private:
    ComponentManager* _components;
    TransformSystem* _transforms;
};

#endif // PHYSICSSYSTEM_H
