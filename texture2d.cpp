#include "texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

Texture2D::Texture2D(string path)
{
    _path = path;
}

Texture2D::~Texture2D()
{
    if(_isAllocate)
    {
        stbi_image_free(_memory);
    }
}

bool Texture2D::Load()
{
    _memory = stbi_load(_path.c_str(), &_width, &_height, &_numComponents, 0);
    if(_memory != nullptr)
    {
        _isAllocate = true;
        return true;
    }
    return false;
}

bool Texture2D::RendererAllocate()
{

}

u32 Texture2D::GetWidth()
{
    return _width;
}

u32 Texture2D::GetHeight()
{
    return _height;
}
