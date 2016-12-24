#include "opengltexture2d.h"

OpenglTexture2D::OpenglTexture2D(string path) : Texture2D(path)
{

}
//TODO : destructor?

bool OpenglTexture2D::RendererAllocate()
{
    assert(!_isGlAllocate);
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);
    if(_numComponents == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _memory);
    else if(_numComponents == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _memory);
    else
    {
        assert(false); // only 4 or 3 color components supported
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    assert(glGetError() == 0);
    _isGlAllocate = true;
    return _handle != 0xFFFFFFFF;
}

GLuint OpenglTexture2D::GetHandle()
{
    return _handle;
}
