#include "openglrenderer.h"

OpenglRenderer::OpenglRenderer(u32 screenWidth, u32 screenHeight) : Renderer(screenWidth, screenHeight)
{

}

OpenglRenderer::~OpenglRenderer()
{

}

Texture2D* OpenglRenderer::CreateTexture()
{
    Texture2D *ret = new OpenglTexture2D();
    return ret;
}

void OpenglRenderer::Flush()
{
    glFlush();
}

inline void OpenglRenderer::ExecuteCommands(void* pushBuffer, u32 pointer)
{
    u8* curCmd = (u8*)pushBuffer;
    while(curCmd < (u8*)pushBuffer + pointer)
    {
        RenderCommandHeader *header = (RenderCommandHeader*)curCmd;
        curCmd += header->size;
        switch(header->type)
        {
            case RenderCommandT_TexturedQuad:
            {
                TexturedQuadRenderCommand *tqrc = (TexturedQuadRenderCommand*)header;
                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf((GLfloat*)&tqrc->mat);
                glBindTexture(GL_TEXTURE_2D, tqrc->rendererHandle);
                glBegin(GL_QUADS);
                glTexCoord2f (tqrc->texRect.x, tqrc->texRect.y);
                glVertex2d(tqrc->rect.x, tqrc->rect.y + tqrc->rect.height); // top left
                glTexCoord2f (tqrc->texRect.x + tqrc->texRect.width, tqrc->texRect.y);
                glVertex2d(tqrc->rect.x + tqrc->rect.width, tqrc->rect.y + tqrc->rect.height); // top right
                glTexCoord2f (tqrc->texRect.x + tqrc->texRect.width, tqrc->texRect.y + tqrc->texRect.height);
                glVertex2d(tqrc->rect.x + tqrc->rect.width, tqrc->rect.y); // bottom right
                glTexCoord2f (tqrc->texRect.x, tqrc->texRect.y + tqrc->texRect.height);
                glVertex2d(tqrc->rect.x, tqrc->rect.y); // bottom left
                glEnd();
            }break;
            default:
                assert(false); // unknown render command
                return;
        }
    }
}

void OpenglRenderer::RenderGame()
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((GLfloat*)&_gameMatrix);
    ExecuteCommands(_pushBuffer, _pushBufferPointer);
    _pushBufferPointer = 0;
}

void OpenglRenderer::RenderUI()
{
    Mat4 projM = ortho(0.0f, (r32)_pixelSize.x, 0.0f, (r32)_pixelSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((GLfloat*)&projM);
    ExecuteCommands(_uiPushBuffer, _uiPushBufferPointer);
    _uiPushBufferPointer = 0;
}

void OpenglRenderer::ClearScreen(r32 r, r32 g, r32 b)
{
    glClearColor(r, g, b,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenglRenderer::Swap()
{
    //glXSwapBuffers(_display, _window);
}

void OpenglRenderer::Initialize()
{
    Renderer::Initialize();
}
