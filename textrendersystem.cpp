#include "textrendersystem.h"

#define TEXT_MASK (COMPONENT_TRANSFORM | COMPONENT_TEXT | COMPONENT_RECTTRANSFORM)

TextRenderSystem::TextRenderSystem()
{

}

void TextRenderSystem::Init(ComponentManager *components, Renderer *renderer)
{
    printf("textrender init\n");

    _components = components;
    _renderer = renderer;

    FT_Error error = FT_Init_FreeType(&_freetypelib);
    if (error)
    {
        std::cerr << "Failed to load freetype!" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(_freetypelib, "arial.ttf", 0, &face))
        printf("ERROR::FREETYPE: Failed to load font\n");

    FT_Set_Pixel_Sizes(face, 0, 64);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        printf("ERROR::FREETYTPE: Failed to load Glyph\n");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("ERROR::FREETYTPE: Failed to load Glyph\n");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            IVec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            IVec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        _characters.insert(std::pair<GLchar, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(_freetypelib);
}

void TextRenderSystem::Update()
{
    for(u32 entity = 0; entity < MAX_ENTITIES; entity++)
    {
        if((_components->masks[entity] & TEXT_MASK) == TEXT_MASK)
        {
            std::cout << "Render text!" << std::endl;

            TextComponent* textc = &_components->texts[entity];
            TransformComponent* transc = &_components->transforms[entity];
            //RectTransformComponent* rtransc = &_components->recttransforms[entity];

            Mat4 projM = ortho(0.0f, 4.0f*1.33333f, 0.0f, 4.0f);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf((GLfloat*)&projM);
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((GLfloat*)&transc->modelMatrix);

            glActiveTexture(GL_TEXTURE0);

            r32 x = 0.0f;
            r32 y = 0.0f;
            r32 scale = transc->scale.x;

            // Iterate through all characters
            std::string::const_iterator c;
            for (c = textc->text.begin(); c != textc->text.end(); c++)
            {
                Character ch = _characters[*c];

                GLfloat xpos = x + ch.Bearing.x * scale;
                GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

                GLfloat w = (r32)ch.Size.x * scale;
                GLfloat h = (r32)ch.Size.y * scale;

                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glBegin(GL_TRIANGLES);

                glTexCoord2f(   0.0, 0.0);
                glVertex2f(xpos,     ypos + h);
                glTexCoord2f(   0.0, 1.0);
                glVertex2f(xpos,     ypos    );
                glTexCoord2f(   1.0, 1.0);
                glVertex2f(xpos + w, ypos    );
                glTexCoord2f(   0.0, 0.0);
                glVertex2f(xpos,     ypos + h);
                glTexCoord2f(   1.0, 1.0);
                glVertex2f(xpos + w, ypos   );
                glTexCoord2f(   1.0, 0.0);
                glVertex2f(xpos + w, ypos + h);
                glEnd();


                x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
            }

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
