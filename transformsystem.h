#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include "componentmanager.h"

class TransformSystem
{
public:
    TransformSystem();
    void Init(ComponentManager* components);
    void SetLocalPosition(u32 entity, Vec2 position);
    void SetScale(u32 entity, Vec2 scale);
    void SetRotation(u32 entity, r32 rotation);
    void Rotate(u32 entity, r32 rotate);
    Vec2 GetAnchor(i32 entity, RectPivot pivot);
    void SetDirty(u32 entity);

    void UpdateDirtyMatrices();

private:
    ComponentManager* _components;
};

#endif // TRANSFORMSYSTEM_H
