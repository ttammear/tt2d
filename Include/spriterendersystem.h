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
    void Update();
    void Init(ComponentManager *components, Renderer *renderer);
    Vec2 GetAnchor(i32 entity, RectPivot pivot);

private:
    ComponentManager* _components;
    Renderer* _renderer;
};

#endif // SPRITERENDERSYSTEM_H