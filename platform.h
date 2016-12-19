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
    virtual bool CreateWindow(u32 width, u32 height, string title);
    virtual void Run();
    void Update(r32 dt);

private:
    Engine _engine;

    /*virtual bool OpenFile(string name);
    virtual bool OpenFile(string name);*/
};

#endif // PLATFORM_H
