#ifndef OPENGLTEXTURE2D_H
#define OPENGLTEXTURE2D_H

#include "texture2d.h"
#include <GL/glew.h>

class OpenglTexture2D : public Texture2D
{
    friend class OpenglRenderer;
public:
    OpenglTexture2D(string path);
    virtual bool RendererAllocate();
    GLuint GetHandle();

private:
    GLuint _handle;
    bool _isGlAllocate = false;
};

#endif // OPENGLTEXTURE2D_H
