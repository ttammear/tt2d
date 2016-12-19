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

bool Platform::CreateWindow(u32 width, u32 height, string title)
{
    _engine.CreateSprite("sprite", "forwardp.jpg");
    return true;
}

void Platform::Update(r32 dt)
{
    _engine.Update(dt);
}

void Platform::Run()
{

}

