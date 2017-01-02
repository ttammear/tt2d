#ifndef OPENGLTEXTURE2D_H
#define OPENGLTEXTURE2D_H

#include "texture2d.h"
#include <GL/glew.h>

class OpenglTexture2D : public Texture2D
{
    friend class OpenglRenderer;
public:
    OpenglTexture2D();
    OpenglTexture2D(const OpenglTexture2D& that) = delete;
    OpenglTexture2D& operator=(const OpenglTexture2D&) = delete;
    ~OpenglTexture2D();
    virtual bool RendererAllocate();
    GLuint GetHandle();

private:
    GLuint _handle;
    bool _isGlAllocate = false;
};

#endif // OPENGLTEXTURE2D_H
