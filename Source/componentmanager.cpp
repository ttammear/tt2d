#include "componentmanager.h"

ComponentManager::ComponentManager()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        masks[entity] = 0;
    }
}

ComponentManager::~ComponentManager()
{
    for (std::map<std::type_index, void*>::iterator it=_customComponents.begin(); it!=_customComponents.end(); ++it)
    {
        printf("component deleted\n");
        // I just don't know how to do this better..
        delete (int*) it->second;
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

bool ComponentManager::HasTag(u32 entity, u32 tag)
{
    assert(entity < MAX_ENTITIES);
    assert(tag < _tagIndex);
    return (masks[entity] & (1 << tag)) != 0;
}
