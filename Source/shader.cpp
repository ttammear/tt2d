#include "shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
    if(_loaded)
    {
        delete _data;
    }
}

bool Shader::LoadFromFile(string filepath)
{
    assert(!_loaded);

    streampos size;

    ifstream file (filepath, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        _data = new u8[size];
        file.seekg (0, ios::beg);
        file.read ((char*)_data, size);
        file.close();
        _loaded = true;
        return true;
    }
    else
    {
        cout << "Unable to open file";
        return false;
    }
}
