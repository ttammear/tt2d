#include "renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Initialize()
{

}

void Renderer::Render()
{

}

void Renderer::PushRenderCommand(RenderCommand command)
{
    renderCommands.push_back(command);
}

void Renderer::ResetPushBuffer()
{
    renderCommands.clear();
}
