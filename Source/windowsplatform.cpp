#include "windowsplatform.h"

#ifdef TT2D_PLATFORM_WINDOWS

WindowsPlatform::WindowsPlatform()
{

}

WindowsPlatform::~WindowsPlatform()
{
    if(_windowCreated)
    {
        wglMakeCurrent(NULL, NULL);
        ReleaseDC(_hWnd, _hDC);
        wglDeleteContext(_hRC);
        DestroyWindow(_hWnd);
    }
}

i32 WindowsPlatform::VirtualKeyToGameKey(WPARAM keycode)
{
    switch(keycode)
    {
    case 0x30:
        return 0; // 0 key
    case 0x31:
        return 0; // 1 key
    case 0x32:
        return 0; // 2 key
    case 0x33:
        return 0; // 3 key
    case 0x34:
        return 0; // 4 key
    case 0x35:
        return 0; // 5 key
    case 0x36:
        return 0; // 6 key
    case 0x37:
        return 0; // 7 key
    case 0x38:
        return 0; // 8 key
    case 0x39:
        return 0; // 9 key
    case 0x41:
        return KEYCODE_A; // A key
    case 0x42:
        return KEYCODE_B; // B key
    case 0x43:
        return KEYCODE_C; // C key
    case 0x44:
        return KEYCODE_D; // D key
    case 0x45:
        return KEYCODE_E; // E key
    case 0x46:
        return KEYCODE_F; // F key
    case 0x47:
        return KEYCODE_G; // G key
    case 0x48:
        return KEYCODE_H; // H key
    case 0x49:
        return KEYCODE_I; // I key
    case 0x4A:
        return KEYCODE_J; // J key
    case 0x4B:
        return KEYCODE_K; // K key
    case 0x4C:
        return KEYCODE_L; // L key
    case 0x4D:
        return KEYCODE_M; // M key
    case 0x4E:
        return KEYCODE_N; // N key
    case 0x4F:
        return KEYCODE_O; // O key
    case 0x50:
        return KEYCODE_P; // P key
    case 0x51:
        return KEYCODE_Q; // Q key
    case 0x52:
        return KEYCODE_R; // R key
    case 0x53:
        return KEYCODE_S; // S key
    case 0x54:
        return KEYCODE_T; // T key
    case 0x55:
        return KEYCODE_U; // U key
    case 0x56:
        return KEYCODE_V; // V key
    case 0x57:
        return KEYCODE_W; // W key
    case 0x58:
        return KEYCODE_X; // X key
    case 0x59:
        return KEYCODE_Y; // Y key
    case 0x5A:
        return KEYCODE_Z; // Z key
    }
    return -1;
}

LONG WINAPI
WindowProcInternal(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WindowsPlatform *c = (WindowsPlatform *)GetWindowLongPtr(hWnd,GWLP_USERDATA);

    if (c == NULL)
        return DefWindowProc(hWnd, msg, wParam, lParam);

    return c->WindowProc(hWnd, msg, wParam, lParam);
}

int WindowsPlatform::WindowProc(HWND hWnd, int uMsg, WPARAM wParam, LPARAM lParam)
{
    //static PAINTSTRUCT ps;
    i32 keyCode;

    switch(uMsg) {

        case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        //PostMessage(hWnd, WM_PAINT, 0, 0);
        return 0;

    case WM_KEYDOWN:
        keyCode = VirtualKeyToGameKey(wParam);
        if(keyCode != -1)
        {
            _engine->_input._input.keyStates[keyCode] = 1;
        }
        return 0;

    case WM_KEYUP:
        keyCode = VirtualKeyToGameKey(wParam);
        if(keyCode != -1)
        {
            _engine->_input._input.keyStates[keyCode] = 0;
        }
        return 0;

        case WM_CHAR:
        switch (wParam) {
        case 27:			/* ESC key */
            PostQuitMessage(0);
            break;
        }
        return 0;

        case WM_CLOSE:
            _running = false;
            PostQuitMessage(0);
        return 0;
        case WM_QUIT:
            _running = false;
            PostQuitMessage(0);
        return 0;
    }

    return (LONG)DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool WindowsPlatform::EnableVsync(bool enable)
{
    if (WGLExtensionSupported("WGL_EXT_swap_control"))
    {
        // Extension is supported, init pointers.
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
        assert(wglSwapIntervalEXT != 0);
        // this is another function from WGL_EXT_swap_control extension
        wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");
        assert(wglGetSwapIntervalEXT != 0);
        wglSwapIntervalEXT(enable ? 1 : 0);
        return true;
    }
    return false;
}

bool WindowsPlatform::Init()
{
    return true;
}

bool WindowsPlatform::TTCreateNewWindow(u32 width, u32 height, string title)
{
    assert(!_windowCreated); // window already created, no multi windows supported at the moment

    int         pf;
    HDC         hDC;
    HWND        hWnd;
    WNDCLASS    wc = {};
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;

    wchar_t wtext[50];
    mbstowcs(wtext, title.c_str(), strlen(title.c_str())+1); //Plus null
    LPWSTR ptr = wtext;

    /* only register the window class once - use hInstance as a flag. */
    if (!hInstance) {
        hInstance = GetModuleHandle(NULL);
        wc.style         = CS_OWNDC;
        wc.lpfnWndProc   = (WNDPROC)WindowProcInternal;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = ptr;

        if (!RegisterClass(&wc)) {
            MessageBox(NULL, L"RegisterClass() failed: Cannot register window class.", L"Error", MB_OK);
            return NULL;
        }
    }
    else
    {
        MessageBoxA(NULL, "No hinstance!\n", ":|", MB_OK);
    }

    hWnd = CreateWindowEx(
                0,                              // Optional window styles.
                ptr,                     // Window class
                wtext,    // Window text
                WS_OVERLAPPEDWINDOW ,  // Window style

                // Size and position
                CW_USEDEFAULT, CW_USEDEFAULT, width, height,

                NULL,       // Parent window
                NULL,       // Menu
                hInstance,  // Instance handle
                NULL        // Additional application data
                );

    if (hWnd == NULL) {
        MessageBox(NULL, L"CreateWindow() failed:  Cannot create a window.", L"Error", MB_OK);
        return false;
    }
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    hDC = GetDC(hWnd);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = 32;

    pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) {
        MessageBoxA(NULL, "ChoosePixelFormat() failed:  "
               "Cannot find a suitable pixel format.", "Error", MB_OK);
        return false;
    }

    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
        MessageBoxA(NULL, "SetPixelFormat() failed:  "
            "Cannot set format specified.", "Error", MB_OK);
        return false;
    }

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    ReleaseDC(hWnd, hDC);

    _hWnd = hWnd;

    // init opengl

    hDC = GetDC(hWnd);				/* opengl context */
    HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);


    _hRC = hRC;
    _hDC = hDC;
    _windowCreated = true;

    if(glewInit() != GLEW_OK)
    {
        printf("Glew Init failed!\n");
        return false;
    }
    if (glewIsSupported("GL_VERSION_3_3"))
    {
        printf("GL 3.3 Supported \n");
    }
    else
    {
        printf("GL 3.3 NOT Supported, exiting!\n");
        return false;
    }

    glColorMask ( 1,1,1,1 );
    glClearColor( 0,0,1,1 );
    glClear     ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_FRAMEBUFFER_SRGB);

    // TODO: is the nCmdShow thing important?
    ShowWindow(hWnd, SW_SHOWDEFAULT);

    return true;
}

HWND WindowsPlatform::GetWindow()
{
    return _hWnd;
}

HGLRC WindowsPlatform::GetGlContext()
{
    return _hRC;
}

void WindowsPlatform::DisableWindowResize()
{

}

void WindowsPlatform::ForceAspectRatio(u32 numerator, u32 denominator)
{

}

bool WindowsPlatform::WGLExtensionSupported(const char *extension_name)
{
    // this is pointer to function which returns pointer to string with list of all wgl extensions
    PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

    // determine pointer to wglGetExtensionsStringEXT function
    _wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) wglGetProcAddress("wglGetExtensionsStringEXT");

    if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
    {
        // string was not found
        return false;
    }

    // extension is supported
    return true;
}

bool WindowsPlatform::ProcessEvents()
{
    for(int i = 0; i < KEY_COUNT; i++)
    {
        _engine->_input._input.keyStatesLastFrame[i] = _engine->_input._input.keyStates[i];
    }

    MSG msg;
    // TODO: handle quit
    while(PeekMessage(&msg, _hWnd, 0, 0, 1))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return _running;
}

void WindowsPlatform::Swap()
{
    //wglSwapLayerBuffers(GetDC(_hWnd), WGL_SWAP_MAIN_PLANE);
    SwapBuffers(_hDC);
}

#endif // TT2D_PLATFORM_WINDOWS
