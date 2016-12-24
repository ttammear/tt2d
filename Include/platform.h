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
    ~Platform();

    bool Init();
    virtual bool CreateWindow(u32, u32, string);
    virtual void Swap();
    virtual bool ProcessEvents();
    void SetEngine(Engine* engine);

protected:
    Engine *_engine;

    /*virtual bool OpenFile(string name);
    virtual bool OpenFile(string name);*/
};

#endif // PLATFORM_H
