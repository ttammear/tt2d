#ifndef SPRITERENDERSYSTEM_H
#define SPRITERENDERSYSTEM_H

#include "componentmanager.h"
#include <GL/glew.h>
#include "opengltexture2d.h"
#include "renderer.h"
#include "ttmath.h"

class SpriteRenderSystem
{
public:
    SpriteRenderSystem();
    SpriteRenderSystem(ComponentManager* components);
    void Update(u32 entities[], u32 numEntities, r32 dt);
    void Init(ComponentManager *components, Renderer *renderer);

private:
    ComponentManager* _components;
    Renderer* _renderer;
};

#endif // SPRITERENDERSYSTEM_H
