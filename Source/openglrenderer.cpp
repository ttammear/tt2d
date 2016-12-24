#include "openglrenderer.h"

OpenglRenderer::OpenglRenderer(u32 screenWidth, u32 screenHeight) : Renderer(screenWidth, screenHeight)
{

}

inline void OpenglRenderer::ExecuteCommands(Mat4* mat, void* pushBuffer, u32 pointer)
{
    glLoadMatrixf((GLfloat*)mat);

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
                glTexCoord2f (0.0f,0.0f);
                glVertex2d(tqrc->topleft.x, tqrc->topleft.y); // top left
                glTexCoord2f (1.0f,0.0f);
                glVertex2d(tqrc->bottomright.x, tqrc->topleft.y); // top right
                glTexCoord2f (1.0f,1.0f);
                glVertex2d(tqrc->bottomright.x, tqrc->bottomright.y); // bottom right
                glTexCoord2f (0.0f,1.0f);
                glVertex2d(tqrc->topleft.x, tqrc->bottomright.y); // bottom left
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
    ExecuteCommands(&_gameMatrix, _pushBuffer, _pushBufferPointer);
    _pushBufferPointer = 0;
}

void OpenglRenderer::RenderUI()
{
    Mat4 projM = ortho(0.0f, (r32)_pixelSize.x, 0.0f, (r32)_pixelSize.y);
    glMatrixMode(GL_PROJECTION);
    ExecuteCommands(&projM, _uiPushBuffer, _uiPushBufferPointer);
    _uiPushBufferPointer = 0;
}

void OpenglRenderer::ClearScreen()
{
    glClearColor(1.0f,0.0f,1.0f,1.0f);
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
