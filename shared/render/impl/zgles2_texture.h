#pragma once

#include <render/impl/zgles2.h>

class zgles2_texture final
{
public:
    zgles2_texture();
    ~zgles2_texture();

    bool load(int width, int height, GLvoid* pixels);
    void unload();

    GLuint get_id() const;

private:
    GLuint m_texture_id;
};
