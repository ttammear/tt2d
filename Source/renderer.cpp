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
    _uiPushBuffer = std::malloc(INITIAL_UI_PUSH_BUFFER_SIZE);
    _pushBuffer = std::malloc(INITIAL_GAME_PUSH_BUFFER_SIZE);
    assert(_uiPushBuffer != nullptr);
    assert(_pushBuffer != nullptr);
    _initialized = true;

    _gameMatrix = ortho(0.0f, (r32)_pixelSize.x, 0.0f, (r32)_pixelSize.y);
}

void Renderer::PushRenderCommand(RenderCommandHeader* command, bool ui)
{
    if(!ui)
    {
        if(_pushBufferPointer + command->size >= _currentGameBufferSize)
        {
            _pushBuffer = realloc(_pushBuffer, _currentGameBufferSize * 2);
            _currentGameBufferSize *= 2;
            // TODO: std error
            printf("WARNING: resizing game push buffer! Consider increasing initial size\n");
        }
        std::memcpy((u8*)_pushBuffer+_pushBufferPointer, command, command->size);
        _pushBufferPointer += command->size;
    }
    else
    {
        if(_uiPushBufferPointer + command->size >= _currentUIBufferSize)
        {
            _uiPushBuffer = realloc(_uiPushBuffer, _currentUIBufferSize * 2);
            _currentUIBufferSize *= 2;
            printf("WARNING: resizing UI push buffer! Consider increasing initial size\n");
        }
        std::memcpy((u8*)_uiPushBuffer+_uiPushBufferPointer, command, command->size);
        _uiPushBufferPointer += command->size;
    }
}

Vec2 Renderer::GetScreenSize()
{
    return Vec2((r32)_pixelSize.x,(r32)_pixelSize.y);
}

#include "opengltexture2d.h"
void Renderer::PushTexturedQuadRenderCommand(Rect rect, Rect texRect, Mat4 mat, u32 textureHandle, bool isUI)
{
    TexturedQuadRenderCommand cmd;
    cmd.rect = rect;
    cmd.texRect = texRect;
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
