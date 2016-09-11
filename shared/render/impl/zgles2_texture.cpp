#include "zgles2_texture.h"

zgles2_texture::zgles2_texture() :
    m_texture_id(0)
{
}

zgles2_texture::~zgles2_texture()
{
    unload();
}

bool zgles2_texture::load(int width, int height, GLvoid* pixels)
{
    unload();

    // Use tightly packed data
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

    // Generate a texture object
    glGenTextures ( 1, &m_texture_id );

    // Bind the texture object
    glBindTexture ( GL_TEXTURE_2D, m_texture_id );

    // Load the texture
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );

    // Set the filtering mode
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    return true;
}

void zgles2_texture::unload()
{
    if(m_texture_id) {
        glDeleteTextures ( 1, &m_texture_id );
        m_texture_id = 0;
    }
}

GLuint zgles2_texture::get_id() const
{
    return m_texture_id;
}
