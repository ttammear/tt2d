#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#define MAX_ENTITIES 60

#include <array>
#include <vector>
#include <map>
#include <typeindex>
#include "components.h"

enum Component
{
    COMPONENT_NONE          =       0,
    COMPONENT_TRANSFORM     =       1 << 0,
    COMPONENT_SPRITE        =       1 << 1,
    COMPONENT_RECTTRANSFORM =       1 << 2,
    COMPONENT_TEXT          =       1 << 3,
    COMPONENT_PHYSICS       =       1 << 4,
    COMPONENT_COLLIDER      =       1 << 5,
    COMPONENT_ANIMSPRITE    =       1 << 6,
    COMPONENT_CUSTOM        =       7           // keep up to date pls
};

using std::array;

using ComponentMask = u32;

class ComponentManager
{
public:
    ComponentManager();

    void AddTag(u32 entity, u32 tag);
    void RemoveTag(u32 entity, u32 tag);
    bool HasTag(u32 entity, u32 tag);
    u32 CreateTag();
    u32 CreateEntity(string name);
    void DeleteEntity(u32 entity);
    void SetActive(u32 entity, bool active);

public:
    ComponentMask masks[MAX_ENTITIES];
    TransformComponent transforms[MAX_ENTITIES];
    RectTransformComponent recttransforms[MAX_ENTITIES];
    SpriteComponent sprites[MAX_ENTITIES];
    AnimatedSpriteComponent animsprites[MAX_ENTITIES];
    TextComponent texts[MAX_ENTITIES];
    CoreComponent names[MAX_ENTITIES];
    PhysicsComponent physics[MAX_ENTITIES];
    ColliderComponent colliders[MAX_ENTITIES];

    u32 _tagIndex = COMPONENT_CUSTOM;
    u32 _entityPtr = 0;
};

#endif // COMPONENTMANAGER_H
