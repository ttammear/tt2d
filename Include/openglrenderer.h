#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "renderer.h"
#include "opengltexture2d.h"
#include <GL/glew.h>

class OpenglRenderer : public Renderer
{
public:
    OpenglRenderer(u32 screenWidth, u32 screenHeight);
    OpenglRenderer(const OpenglRenderer& that) = delete;
    OpenglRenderer& operator=(const OpenglRenderer&) = delete;
    ~OpenglRenderer();

    void Initialize();
    void RenderUI();
    void RenderGame();
    void ClearScreen(r32 r, r32 g, r32 b);
    void Swap();
    void Flush();
    Texture2D* CreateTexture();

private:
    void ExecuteCommands(void* pushBuffer, u32 pointer);
};

#endif // OPENGLRENDERER_H
