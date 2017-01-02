#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include "shared.h"
#include "engine.h"

using std::string;

class Platform
{
public:
    Platform();
    Platform(const Platform& that) = delete;
    Platform& operator=(const Platform&) = delete;
    virtual ~Platform();

    bool Init();
    // Thank microsoft for defining a 'CreateWindow' macro
    virtual bool TTCreateNewWindow(u32, u32, string);
    virtual void DisableWindowResize() = 0;
    virtual bool EnableVsync(bool enable) = 0;
    virtual void ForceAspectRatio(u32 numerator, u32 denominator) = 0;
    virtual void Swap();
    virtual bool ProcessEvents();
    void SetEngine(Engine* engine);

protected:
    Engine *_engine;

    /*virtual bool OpenFile(string name);
    virtual bool OpenFile(string name);*/
};

#endif // PLATFORM_H
