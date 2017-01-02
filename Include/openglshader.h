#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

/*
 * NOT USED AND DO NOT USE
 *
 */

#include "shader.h"
#include "GL/glew.h"

const char vert[] = "#version 330   \n\
uniform mat4 modelMatrix;           \n\
uniform mat4 perspectiveMatrix;     \n\
                                    \n\
void main()                         \n\
{                                   \n\
   gl_Position = gl_Position;       \n\
}";

const char frag[] = "#version 330    \n\
void main()                          \n\
{                                    \n\
    gl_FragColor = gl_FragColor;     \n\
}";

class OpenglShader : public Shader
{
public:
    OpenglShader();
    void CreateProgram();
    void Bind();
    void Unbind();

private:
    GLuint _program = 0xFFFFFFFF;
};

#endif // OPENGLSHADER_H
