#include <iostream>

#include <platform/iresource.h>

#include "zgles2_program.h"

zgles2_program::zgles2_program() :
    m_program(0)
{
}

zgles2_program::~zgles2_program()
{
    unload();
}

bool zgles2_program::load(const iresource* resource,
          const std::string& vertex_shader,
          const std::string& fragment_shader,
          const std::vector<std::string>& attributes,
          const std::vector<std::string>& uniforms)
{
    unload();

    const auto vShaderStr = resource->get_text_resource(vertex_shader);
    const auto fShaderStr = resource->get_text_resource(fragment_shader);

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = load_shader( GL_VERTEX_SHADER, (const char*) vShaderStr.data() );
    fragmentShader = load_shader( GL_FRAGMENT_SHADER,  (const char*) fShaderStr.data() );

    if(0 == vertexShader || 0 == fragmentShader) {
        return false;
    }

    // Create the program object
    programObject = glCreateProgram();

    if ( programObject == 0 ) {
        return false;
    }

    glAttachShader( programObject, vertexShader );
    glAttachShader( programObject, fragmentShader );

    // Link the program
    glLinkProgram( programObject );

    // Check the link status
    glGetProgramiv( programObject, GL_LINK_STATUS, &linked );

    if( !linked ) {
        GLint infoLen = 0;
        glGetProgramiv( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        if( infoLen > 1 ) {
            char* infoLog = (char*) malloc (sizeof(char) * infoLen );
            glGetProgramInfoLog( programObject, infoLen, NULL, infoLog );
            std::cerr << "Error linking program:\n" << infoLog << std::endl;
            free( infoLog );
        }
        glDeleteProgram( programObject );
        return false;
    }

    // Store the program object
    m_program = programObject;

    for(size_t i = 0; i < attributes.size(); i++) {
        const std::string& name = attributes[i];
        m_attributes[name] = glGetAttribLocation(programObject, name.c_str());
    }

    for(size_t i = 0; i < uniforms.size(); i++) {
        const std::string& name = uniforms[i];
        m_uniforms[name] = glGetUniformLocation(programObject, name.c_str());
    }

    return true;
}

GLuint zgles2_program::get_id() const
{
    return m_program;
}

int zgles2_program::get_attribute_location(const std::string& attribute) const
{
    auto search = m_attributes.find(attribute);
    int location = 0;
    if(search != m_attributes.end()) {
        location = search->second;
    }
    return location;
}

int zgles2_program::get_uniform_location(const std::string& uniform) const
{
    auto search = m_uniforms.find(uniform);
    int location = 0;
    if(search != m_uniforms.end()) {
        location = search->second;
    }
    return location;
}

void zgles2_program::unload()
{
    if (m_program) {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

GLuint zgles2_program::load_shader( GLenum type, const char *shaderSrc )
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader ( type );

    if ( shader == 0 ) {
        return 0;
    }

    // Load the shader source
    glShaderSource ( shader, 1, &shaderSrc, NULL );

    // Compile the shader
    glCompileShader ( shader );

    // Check the compile status
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

    if ( !compiled ) {
        GLint infoLen = 0;
        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
        if ( infoLen > 1 ) {
            char* infoLog = (char*) malloc (sizeof(char) * infoLen );
            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            std::cerr << "Error compiling shader:\n" << infoLog << std::endl;
            free ( infoLog );
        }
        glDeleteShader ( shader );
        return 0;
    }
    return shader;
}

