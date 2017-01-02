#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include "shared.h"

#ifdef TT2D_PLATFORM_WINDOWS

#include "platform.h"
#include "input.h"
#include <windows.h>
#include <GL/glew.h>
#include "wglext.h"


class WindowsPlatform : public Platform
{
public:
    WindowsPlatform();
    WindowsPlatform(const WindowsPlatform& that) = delete;
    WindowsPlatform& operator=(const WindowsPlatform&) = delete;
    ~WindowsPlatform();

    bool Init();
    bool TTCreateNewWindow(u32 width, u32 height, string title);
    void DisableWindowResize();
    void ForceAspectRatio(u32 numerator, u32 denominator);
    bool ProcessEvents();
    void Swap();
    bool EnableVsync(bool enable);

    i32 VirtualKeyToGameKey(WPARAM keycode);
    int WindowProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam);
    HWND GetWindow();
    HGLRC GetGlContext();
    bool WGLExtensionSupported(const char *extension_name);
private:
    u32 _width;
    u32 _height;

    HWND _hWnd;
    HDC _hDC;
    HGLRC _hRC;

    bool _windowCreated = false;
    bool _running = true;

    PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = 0;
    PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = 0;
};

#endif // TT2D_PLATFORM_WINDOWS

#endif // WINDOWSPLATFORM_H
