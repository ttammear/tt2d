#include "tt2d.h"

Platform* TT2DCreatePlatform()
{
#ifdef TT2D_PLATFORM_WINDOWS
    return new WindowsPlatform();
#else
    return new LinuxPlatform();
#endif
}
