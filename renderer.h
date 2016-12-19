#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

using std::vector;

struct RenderCommand
{
    int type;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();
    virtual void Initialize();
    void PushRenderCommand(RenderCommand command);
    void ResetPushBuffer();
    virtual void Render();

private:
    vector<RenderCommand> renderCommands;
};

#endif // RENDERER_H
