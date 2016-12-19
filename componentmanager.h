#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#define MAX_ENTITIES 1000

#include <array>
#include "components.h"

enum Component
{
    COMPONENT_NONE          =       0,
    COMPONENT_TRANSFORM     =       1 << 0,
    COMPONENT_SPRITE        =       1 << 1,
};

using std::array;

using ComponentMask = u32;

class ComponentManager
{
public:
    ComponentManager();
public:
    array<ComponentMask, MAX_ENTITIES> masks;
    array<TransformComponent, MAX_ENTITIES> transforms;
    array<SpriteComponent, MAX_ENTITIES> sprites;
};

#endif // COMPONENTMANAGER_H