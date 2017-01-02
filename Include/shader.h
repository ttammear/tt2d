#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>
#include "shared.h"

using namespace std;

class Shader
{
public:
    Shader();
    Shader(const Shader& that) = delete;
    virtual ~Shader();

    bool LoadFromFile(string filepath);

private:
    bool _loaded = false;
    u8* _data = nullptr;
};

#endif // SHADER_H
