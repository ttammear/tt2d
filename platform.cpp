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
    Entity sprite1 =_engine.CreateSprite("sprite", "forwardp.jpg", SPRITEPIVOT_CENTER, SPRITEPIVOT_CENTER);
    Entity sprite2 =_engine.CreateSprite("sprite2", "forwardp.jpg", SPRITEPIVOT_CENTER, SPRITEPIVOT_BOTTOMRIGHT, sprite1);
    Entity sprite3 =_engine.CreateSprite("sprite3", "test.jpg", SPRITEPIVOT_TOPLEFT, SPRITEPIVOT_BOTTOMLEFT, sprite2);
    //_engine.
    return true;
}

void Platform::Update(r32 dt)
{
    _engine.Update(dt);
}

void Platform::Run()
{

}

