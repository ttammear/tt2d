#include "renderer.h"

Renderer::Renderer(u32 screenWidth, u32 screenHeight)
{
    _pixelSize.x = screenWidth;
    _pixelSize.y = screenHeight;
    _aspectRatio = (r32)screenHeight/(r32)screenHeight;
}

Renderer::~Renderer()
{
    if(_initialized)
    {
        free(_uiPushBuffer);
        free(_pushBuffer);
    }
}

void Renderer::Initialize()
{
    _uiPushBuffer = std::malloc(UI_PUSH_BUFFER_SIZE);
    _pushBuffer = std::malloc(GAME_PUSH_BUFFER_SIZE);
    assert(_uiPushBuffer != nullptr);
    assert(_pushBuffer != nullptr);
    _initialized = true;

    _gameMatrix = ortho(0.0f, (r32)_pixelSize.x, 0.0f, (r32)_pixelSize.y);
}

void Renderer::RenderUI()
{

}

void Renderer::RenderGame()
{

}

void Renderer::ClearScreen()
{

}

void Renderer::Swap()
{

}

void Renderer::PushRenderCommand(RenderCommandHeader* command, bool ui)
{
    if(!ui)
    {
        std::memcpy((u8*)_pushBuffer+_pushBufferPointer, command, command->size);
        _pushBufferPointer += command->size;
        assert(_pushBufferPointer < GAME_PUSH_BUFFER_SIZE);
    }
    else
    {
        std::memcpy((u8*)_uiPushBuffer+_uiPushBufferPointer, command, command->size);
        _uiPushBufferPointer += command->size;
        assert(_uiPushBufferPointer < UI_PUSH_BUFFER_SIZE);
    }
}

void Renderer::ResetPushBuffer()
{
    renderCommands.clear();
}

Vec2 Renderer::GetScreenSize()
{
    return Vec2(_pixelSize.x,_pixelSize.y);
}

#include "opengltexture2d.h"
void Renderer::PushTexturedQuadRenderCommand(Vec2 topleft, Vec2 bottomright, Mat4 mat, u32 textureHandle, bool isUI)
{
    TexturedQuadRenderCommand cmd;
    cmd.topleft = topleft;
    cmd.bottomright = bottomright;
    cmd.rendererHandle = textureHandle;
    cmd.size = sizeof(cmd);
    cmd.type = RenderCommandT_TexturedQuad;
    cmd.mat = mat;
    PushRenderCommand(&cmd, isUI);
}

void Renderer::Rescale(IVec2 newSize)
{
    _pixelSize.x = newSize.x;
    _pixelSize.y = newSize.y;
    _aspectRatio = (r32)newSize.x/(r32)newSize.y;
}
