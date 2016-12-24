#ifndef TEXTRENDERSYSTEM_H
#define TEXTRENDERSYSTEM_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include "ttmath.h"

#include "componentmanager.h"
#include "renderer.h"
#include <GL/glew.h>
#include <iostream>

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    IVec2 Size;       // Size of glyph
    IVec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class TextRenderSystem
{
public:
    TextRenderSystem();
    void SetText(u32 entity, std::string text);
    void Render();
    void Init(ComponentManager *components, Renderer *renderer);

private:
    ComponentManager *_components;
    Renderer *_renderer;
    FT_Library _freetypelib;
    std::map<GLchar, Character> _characters;
};

#endif // TEXTRENDERSYSTEM_H
