#ifndef LINUXPLATFORM_H
#define LINUXPLATFORM_H

#include "shared.h"
#ifdef TT2D_PLATFORM_LINUX

#include "platform.h"
#include <X11/Xlib.h>
#include <sys/resource.h>
#include <GL/glew.h>
#include <GL/glx.h>

#include "input.h"

#define SWAPINTERVALFUNC(name) void name(Display *dpy, GLXDrawable drawable, int interval)
typedef SWAPINTERVALFUNC(glXSwapIntervalEXT_t);

class LinuxPlatform : public Platform
{
public:
    LinuxPlatform();
    LinuxPlatform(const LinuxPlatform& that) = delete;
    LinuxPlatform& operator=(const LinuxPlatform&) = delete;
    ~LinuxPlaform();
    bool Init();
    bool TTCreateNewWindow(u32 width, u32 height, string title);
    bool EnableVsync(bool enable);
    void DisableWindowResize();
    void ForceAspectRatio(u32 numerator, u32 denominator);
    bool ProcessEvents();
    void Swap();
private:
    Display* _display;
    Window _window;
    Atom _wmDeleteMessage;
    u32 _width;
    u32 _height;
};

#endif // platform guard

#endif // LINUXPLATFORM_H
