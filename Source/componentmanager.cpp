#include "componentmanager.h"

ComponentManager::ComponentManager()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        masks[entity] = 0;
        names[entity].flags = 0;
    }
}

u32 ComponentManager::CreateTag()
{
    u32 ret = _tagIndex++;
    // we use bitfield of 32 bits at the moment
    // so we can only have 32 tags!
    assert(ret < 31);
    return ret;
}

void ComponentManager::AddTag(u32 entity, u32 tag)
{
    assert(entity < MAX_ENTITIES);
    assert(tag < 31);
    masks[entity] |= (1 << tag);
}

void ComponentManager::RemoveTag(u32 entity, u32 tag)
{
    assert(entity < MAX_ENTITIES);
    assert(tag < 31);
    masks[entity] &= ~(1 << tag);
}

bool ComponentManager::HasTag(u32 entity, u32 tag)
{
    assert(entity < MAX_ENTITIES);
    assert(tag < _tagIndex);
    return (masks[entity] & (1 << tag)) != 0;
}

u32 ComponentManager::CreateEntity(string name)
{
    u32 entity = 0xFFFFFFFF;

    for(u32 e = 0; e < _entityPtr; e++)
    {
        if((names[e].flags & COREFLAG_OCCUPIED) == 0)
        {
            entity = e;
            break;
        }
    }

    if(entity == 0xFFFFFFFF)
        entity = _entityPtr++;
    masks[entity] = COMPONENT_NONE;
    names[entity].name.assign(name);
    names[entity].flags = COREFLAG_ACTIVE | COREFLAG_OCCUPIED;
    return entity;
}

void ComponentManager::DeleteEntity(u32 entity)
{
    masks[entity] = COMPONENT_NONE;
    names[entity].flags = 0;
}

void ComponentManager::SetActive(u32 entity, bool active)
{
    if(active)
        names[entity].flags |= COREFLAG_ACTIVE;
    else
        names[entity].flags &= (~COREFLAG_ACTIVE);
}
