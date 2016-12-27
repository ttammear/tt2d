#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#define MAX_ENTITIES 100

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
    COMPONENT_CUSTOM        =       6           // keep up to date pls
};

using std::array;

using ComponentMask = u32;

class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager();

    void AddTag(u32 entity, u32 tag);
    bool HasTag(u32 entity, u32 tag);
    u32 CreateTag();

    // TEMPLATE MADNESS
    // the destructor of the components will not be called!
    // but since the components are POD, we don't care!
    template<class TYPE> u32 AddComponent()
    {
        if(std::is_pod<TYPE>::value)
        {
            auto array = new TYPE[MAX_ENTITIES];
            _customComponents.insert(std::pair<std::type_index, void*>(typeid(TYPE), (void*) array));
            return _tagIndex++;
        }
        else
        {
            // Components must be plain data!
            assert(false);
        }
    }

    template<class TYPE> TYPE* GetComponentArray()
    {
        auto ret = (TYPE*) _customComponents.at(typeid(TYPE));
        return ret;
    }

public:
    ComponentMask masks[MAX_ENTITIES];
    TransformComponent transforms[MAX_ENTITIES];
    RectTransformComponent recttransforms[MAX_ENTITIES];
    SpriteComponent sprites[MAX_ENTITIES];
    TextComponent texts[MAX_ENTITIES];
    NameComponent names[MAX_ENTITIES];
    PhysicsComponent physics[MAX_ENTITIES];
    ColliderComponent colliders[MAX_ENTITIES];

    u32 _tagIndex = COMPONENT_CUSTOM;
    std::map<std::type_index, void*> _customComponents;
};

#endif // COMPONENTMANAGER_H
