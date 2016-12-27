#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "renderer.h"
#include "opengltexture2d.h"
#include <GL/glew.h>

class OpenglRenderer : public Renderer
{
public:
    OpenglRenderer(u32 screenWidth, u32 screenHeight);

    void Initialize();
    void RenderUI();
    void RenderGame();
    void ClearScreen();
    void Swap();

private:
    void ExecuteCommands(void* pushBuffer, u32 pointer);
};

#endif // OPENGLRENDERER_H
