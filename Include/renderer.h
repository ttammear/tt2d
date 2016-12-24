#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <cstdlib>
#include <cstring>
#include "ttmath.h"
#include "texture2d.h"

#define UI_PUSH_BUFFER_SIZE 5*1024*1024
#define GAME_PUSH_BUFFER_SIZE 5*1024*1024

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
    Vec2 topleft;
    Vec2 bottomright;
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
    virtual ~Renderer();
    virtual void Initialize();
    void SetTransform(CameraTransform transform);
    void PushTexturedQuadRenderCommand(Vec2 topleft, Vec2 bottomright, Mat4 mat, u32 textureHandle, bool isUI);
    void ResetPushBuffer();
    Vec2 GetScreenSize();
    void Rescale(IVec2 newSize);
    virtual void RenderGame();
    virtual void RenderUI();
    virtual void ClearScreen();
    virtual void Swap();

protected:
    void PushRenderCommand(RenderCommandHeader* command, bool ui);

    void* _uiPushBuffer = 0;
    u32 _uiPushBufferPointer = 0;
    void* _pushBuffer = 0;
    u32 _pushBufferPointer = 0;

    Mat4 _gameMatrix;

    vector<RenderCommandHeader> renderCommands;
    CameraTransform _cameraTransform;
    IVec2 _pixelSize;
    r32 _aspectRatio;

    bool _initialized = false;
};

#endif // RENDERER_H
