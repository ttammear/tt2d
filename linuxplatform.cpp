#include "linuxplatform.h"

LinuxPlatform::LinuxPlatform()
{

}

bool LinuxPlatform::Init()
{
    _display = XOpenDisplay(":0.0");

    return Platform::Init();
}

bool LinuxPlatform::CreateWindow(u32 width, u32 height, std::__cxx11::string title)
{
    if (!_display )
        printf( "Cannot open X display\n" );
    int screen = DefaultScreen( _display );
    Window root_win = RootWindow( _display, screen );
    if ( !glXQueryExtension( _display, 0, 0 ) )
        printf( "X Server doesn't support GLX extension\n" );
    int attrib_list[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER, True,
        GLX_SAMPLE_BUFFERS  , 0, // 1 and 4 for 4xAA ??
        GLX_SAMPLES         , 0,
        None};
    int nElements = 0;
    GLXFBConfig* fbconfig = glXChooseFBConfig( _display, screen, attrib_list, &nElements);
    if ( !fbconfig )
    {
        printf( "Failed to get GLXFBConfig\n" );
        exit(1);
    }
    XVisualInfo *visinfo = glXGetVisualFromFBConfig( _display, *fbconfig );
    if ( !visinfo )
    {
        printf( "Failed to get XVisualInfo\n" );
        exit(1);
    }

    // Create the X window
    XSetWindowAttributes winAttr ;
    winAttr.event_mask = StructureNotifyMask | KeyPressMask| KeyReleaseMask | PointerMotionMask;
    winAttr.background_pixmap = None ;
    winAttr.background_pixel  = 0    ;
    winAttr.border_pixel      = 0    ;
    winAttr.colormap = XCreateColormap( _display, root_win,
                                        visinfo->visual, AllocNone );
    unsigned int mask = CWBackPixmap | CWBorderPixel | CWColormap | CWEventMask;
    const int   WIN_XPOS    = 150;
    const int   WIN_YPOS    = 150;
    Window win = XCreateWindow (_display, root_win,
                                WIN_XPOS, WIN_YPOS,
                                width, height, 0,
                                visinfo->depth, InputOutput,
                                visinfo->visual, mask, &winAttr ) ;
    XStoreName( _display, win, title.c_str());
    // Create an OpenGL context and attach it to our X window
    GLXContext context = glXCreateContext( _display, visinfo, NULL, GL_TRUE);
    if (!glXMakeCurrent(_display, win, context))
        printf("glXMakeCurrent failed.\n");
    if (!glXIsDirect(_display,glXGetCurrentContext()))
        printf( "Indirect GLX rendering context obtained\n");
    XMapWindow(_display, win);
    if (!glXMakeCurrent(_display,win,context))
        printf("glXMakeCurrent failed.\n");
    glViewport  ( 0,0,width,height);
    glColorMask ( 1,1,1,1 );
    glClearColor( 0,0,1,1 );
    glClear     ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    _window = win;

    glXSwapIntervalEXT_t* glXSwapInterval = (glXSwapIntervalEXT_t*)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
    if(glXSwapInterval == 0)
    {
        printf("Enabling vsync failed!\n");
    }
    else
    {
        // enable vsync
        GLXDrawable drawable = glXGetCurrentDrawable();
        if (drawable) {
            glXSwapInterval(_display, drawable, 1);
        }
    }

    _wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(_display, _window, &_wmDeleteMessage, True);

    if(glewInit() != GLEW_OK)
    {
        printf("Glew Init failed!\n");
        return false;
    }
    if (glewIsSupported("GL_VERSION_4_4"))
    {
        printf("GL 4.4 Supported \n");
    }
    else
    {
        printf("GL 4.4 NOT Supported, exiting!\n");
        return false;
    }
    return Platform::CreateWindow(width, height, title);
}

void LinuxPlatform::Run()
{
    glEnable(GL_FRAMEBUFFER_SRGB);

    XEvent event;
    b32 running = true;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while(running)
    {
        while (XPending(_display) > 0)
        {
            // Fetch next event:
            XNextEvent(_display, &event);
            char buffer[20];
            int bufsize = 20;
            KeySym key;
            XComposeStatus compose;
            //int charcount;
            // Process the event:
            switch (event.type) {
            case ClientMessage:
                if (event.xclient.data.l[0] == (long)_wmDeleteMessage)
                {
                    printf("Delete message! Exiting...\n");
                    running = false;
                }
                break;
            case MotionNotify:
                //input.mousePosition.x = event.xmotion.x;
                //input.mousePosition.y = event.xmotion.y;

                //input.mouseCoord.x = (input.mousePosition.x/width)*2.0f - 1.0f;
                //input.mouseCoord.y = (1.0 - (input.mousePosition.y/height))*2.0f - 1.0f;
                //pMouse(event.xmotion.x,event.xmotion.y);
                break;
            case KeyPress:
                {
                    // TODO: ther could be multiple characters?
                    XLookupString((XKeyEvent*)&event, buffer, bufsize, &key, &compose);
                    //int keycode = charToKeycode(buffer[0]);
                    //input.keyStates[keycode] = 1;;
                }
                break;
            case KeyRelease:
                {
                    XLookupString((XKeyEvent*)&event, buffer, bufsize, &key, &compose);
                    //int keycode = charToKeycode(buffer[0]);
                    //input.keyStates[keycode] = 0;
                }
                break;
            case ConfigureNotify:
                {
                    XConfigureEvent xce = event.xconfigure;
                    // TODO: this event might not always be a resize event?
                    /*width = */xce.width;
                    /*height = */xce.height;
                    //reshape(eMem,xce.width,xce.height);
                }
                break;
            }
        }

        glClearColor(1.0f,0.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        struct timespec last = start;
        clock_gettime(CLOCK_MONOTONIC, &start);
        float seconds = start.tv_sec-last.tv_sec+(start.tv_nsec-last.tv_nsec)/1000000000.0;

        Platform::Update(seconds);

        printf("frame time: %f err: %d\n", seconds, glGetError());
        glXSwapBuffers(_display, _window);

        /*for(int i = 0; i < KEY_COUNT; i++)
        {
            input.keyStatesLastFrame[i] = input.keyStates[i];
        }*/
    }
}
