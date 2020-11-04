#include <iostream>
#include <algorithm>

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

bool zgles2_program::load(const iresource& resource,
          const std::string& vertex_shader,
          const std::string& fragment_shader,
          const std::set<std::string>& attributes,
          const std::set<std::string>& uniforms)
{
    unload();

    const auto vShaderStr = resource.get_text_resource(vertex_shader);
    const auto fShaderStr = resource.get_text_resource(fragment_shader);

    //std::cout << "vShaderStr\n" << vShaderStr << std::endl;
    //std::cout << "fShaderStr\n" << fShaderStr << std::endl;

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

    for(auto const& name : attributes) {
        m_attributes.emplace_back(name, glGetAttribLocation(programObject, name.c_str()));
    }

    for(auto const& name : uniforms) {
        m_uniforms.emplace_back(name, glGetUniformLocation(programObject, name.c_str()));
    }

    return true;
}

GLuint zgles2_program::get_id() const
{
    return m_program;
}

int zgles2_program::get_attribute_location(const std::string& attribute) const
{
    auto it = std::lower_bound(m_attributes.begin(), m_attributes.end(), attribute, [](const auto& pair, auto const& str){
        return pair.first < str;
    });
    int location = -1;
    if(it != m_attributes.end() && it->first == attribute) {
        location = it->second;
    }
    return location;
}

int zgles2_program::get_uniform_location(const std::string& uniform) const
{
    auto it = std::lower_bound(m_uniforms.begin(), m_uniforms.end(), uniform, [](const auto& pair, auto const& str){
        return pair.first < str;
    });    
    int location = -1;
    if(it != m_uniforms.end() && it->first == uniform) {
        location = it->second;
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
