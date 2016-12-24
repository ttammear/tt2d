#include "platform.h"

Platform::Platform()
{

}

Platform::~Platform()
{

}

bool Platform::Init()
{
    return true;
}

bool Platform::CreateWindow(u32, u32, string)
{
    return true;
}

void Platform::SetEngine(Engine *engine)
{
    _engine = engine;
}

bool Platform::ProcessEvents()
{
    return true;
}

void Platform::Swap()
{

}

