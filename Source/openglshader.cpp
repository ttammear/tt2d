#include "openglshader.h"

OpenglShader::OpenglShader()
{

}


GLuint createShader(GLenum eShaderType, const char* shaderData, int fsize)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = shaderData;
    glShaderSource(shader, 1, &strFileData, &fsize);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch(eShaderType)
        {
        case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
        case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        free(strInfoLog);
    }

    return shader;
}

// TODO: remove this moronic error 'handling'
void OpenglShader::CreateProgram()
{
    GLuint vertShader = createShader(GL_VERTEX_SHADER, vert, sizeof(vert));
    GLuint fragShader = createShader(GL_FRAGMENT_SHADER, frag, sizeof(frag));

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    int glerror = glGetError();
    if(glerror != 0)
    {
        printf("Error: %d\n", glerror);
        assert(false);
    }

    glLinkProgram(program);

    glerror = glGetError();
    if(glerror != 0)
    {
        printf("Error: %d\n", glerror);
        assert(false);
    }

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    GLint infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    glerror = glGetError();
    if(glerror != 0)
    {
        printf("Error: %d\n", glerror);
        assert(false);
    }
    if (infoLogLength > 0)
    {
        if(glerror != 0)
        {
            printf("Error: %d\n", glerror);
            assert(false);
        }

        GLchar *strInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        glerror = glGetError();
        if(glerror != 0)
        {
            printf("Error: %d\n", glerror);
            assert(false);
        }
        printf("Linker failure: %s\n", strInfoLog);
        free(strInfoLog);
    }

    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    _program = program;
}

void OpenglShader::Bind()
{
    assert(_program != 0xFFFFFFFF);
    glUseProgram(_program);
}

void OpenglShader::Unbind()
{
    glUseProgram(0);
}
