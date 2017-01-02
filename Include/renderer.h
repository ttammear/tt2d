#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <cstdlib>
#include <cstring>
#include "ttmath.h"
#include "texture2d.h"

#define INITIAL_UI_PUSH_BUFFER_SIZE 5*1024
#define INITIAL_GAME_PUSH_BUFFER_SIZE 5*1024

using std::vector;

enum RenderCommandType
{
    RenderCommandT_TexturedQuad,
};

struct RenderCommandHeader
{
    RenderCommandType type;
    u32 size;
};

struct TexturedQuadRenderCommand : RenderCommandHeader
{
    Rect rect;
    Rect texRect;
    u32 rendererHandle;
    Mat4 mat;
};

struct CameraTransform
{
    r32 unitsToPixels;
    Vec2 screenCenter;
};

class Renderer
{
    friend class Engine;
public:
    Renderer(u32 width, u32 height);
    Renderer(const Renderer& that) = delete;
    Renderer& operator=(const Renderer&) = delete;
    virtual ~Renderer();
    void Initialize();
    void SetTransform(CameraTransform transform);
    void PushTexturedQuadRenderCommand(Rect rect, Rect texRect, Mat4 mat, u32 textureHandle, bool isUI);
    Vec2 GetScreenSize();
    void Rescale(IVec2 newSize);
    virtual void RenderGame() = 0;
    virtual void RenderUI() = 0;
    // TODO: make this a render command
    virtual void ClearScreen(r32 r, r32 g, r32 b) = 0;
    virtual void Swap() = 0;
    virtual void Flush() = 0;
    virtual Texture2D* CreateTexture() = 0;

protected:
    void PushRenderCommand(RenderCommandHeader* command, bool ui);

    void* _uiPushBuffer = 0;
    u32 _uiPushBufferPointer = 0;
    void* _pushBuffer = 0;
    u32 _pushBufferPointer = 0;

    u32 _currentGameBufferSize = INITIAL_GAME_PUSH_BUFFER_SIZE;
    u32 _currentUIBufferSize = INITIAL_UI_PUSH_BUFFER_SIZE;

    Mat4 _gameMatrix;

    CameraTransform _cameraTransform;
    IVec2 _pixelSize;
    r32 _aspectRatio;

    bool _initialized = false;
};

#endif // RENDERER_H
