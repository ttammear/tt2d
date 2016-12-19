#ifndef LINUXPLATFORM_H
#define LINUXPLATFORM_H

#include "platform.h"
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>

#define SWAPINTERVALFUNC(name) void name(Display *dpy, GLXDrawable drawable, int interval)
typedef SWAPINTERVALFUNC(glXSwapIntervalEXT_t);

class LinuxPlatform : Platform
{
public:
    LinuxPlatform();
    bool Init();
    bool CreateWindow(u32 width, u32 height, string title);
    void Run();
private:
    Display* _display;
    Window _window;
    Atom _wmDeleteMessage;
};

#endif // LINUXPLATFORM_H
