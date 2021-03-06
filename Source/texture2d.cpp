#include "texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::~Texture2D()
{
    if(_isAllocate)
    {
        stbi_image_free(_memory);
    }
}

bool Texture2D::Load(string path)
{
    _path = path;
    _memory = stbi_load(_path.c_str(), &_width, &_height, &_numComponents, 0);
    printf("components: %d\n",_numComponents);
    if(_memory != nullptr)
    {
        _isAllocate = true;
        return true;
    }
    assert(false);
    return false;
}

bool Texture2D::RendererAllocate()
{
    return true;
}

u32 Texture2D::GetWidth()
{
    return _width;
}

u32 Texture2D::GetHeight()
{
    return _height;
}
