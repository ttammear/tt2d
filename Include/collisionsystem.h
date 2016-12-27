#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "componentmanager.h"

class CollisionSystem
{
public:
    CollisionSystem();
    void Init(ComponentManager *components);
    void Update();
    void AddCollider(u32 entity);
    void SetCallback(u32 entity, CollisionCallback_t* callback, void *userData);

protected:
    ComponentManager* _components;
};

#endif // COLLISIONSYSTEM_H
