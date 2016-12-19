#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include "shared.h"

using std::string;

class Texture2D
{
public:
    Texture2D() = default;
    Texture2D(string path);
    ~Texture2D();

    bool Load();
    virtual bool RendererAllocate();

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
