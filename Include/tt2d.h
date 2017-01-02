#ifndef TT2D_H
#define TT2D_H

#include "engine.h"
#ifdef TT2D_PLATFORM_WINDOWS
#include "windowsplatform.h"
#else
#include "linuxplatform.h"
#endif

Platform* TT2DCreatePlatform();


#endif // TT2D_H
