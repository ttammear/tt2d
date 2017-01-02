#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include "shared.h"

using std::string;

class Texture2D
{
public:
    Texture2D() = default;
    Texture2D(const Texture2D& that) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    virtual ~Texture2D();

    bool Load(string path);
    virtual bool RendererAllocate();
    u32 GetWidth();
    u32 GetHeight();

protected:
    void* _memory;
    i32 _width;
    i32 _height;
    i32 _numComponents;

    bool _isAllocate = false;
    string _path;
private:

};

#endif // TEXTURE2D_H
