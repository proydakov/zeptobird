#pragma once

#include <set>
#include <string>
#include <vector>
#include <utility>

#include <render/impl/zgles2.h>

class iresource;

class zgles2_program final
{
public:
    zgles2_program();
    ~zgles2_program();

    bool load(const iresource& resource,
              const std::string& vertex_shader,
              const std::string& fragment_shader,
              const std::set<std::string>& attributes,
              const std::set<std::string>& uniforms);

    void unload();

    GLuint get_id() const;
    int get_attribute_location(const std::string& attribute) const;
    int get_uniform_location(const std::string& uniform) const;

private:
    GLuint load_shader( GLenum type, const char *shaderSrc );

private:
    GLuint m_program;

    std::vector<std::pair<std::string, int>> m_attributes;
    std::vector<std::pair<std::string, int>> m_uniforms;
};
