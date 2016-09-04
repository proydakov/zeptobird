#include <cassert>
#include <vector>
#include <iostream>

#include <platform/iresource.h>
#include <render/imodel.h>

#include "zgles2.h"
#include "zgles2_render.h"

namespace {
    GLuint load_shader_impl( GLenum type, const char *shaderSrc );
}

struct zgles2_render::data
{
    data();

    zcolor background_color;

    std::vector<GLfloat> buffer;

    GLuint program;
    int    prog_color;

    bool flag = false;
};

zgles2_render::data::data()
{
    background_color = {0.65f, 0.65f, 0.65f};
    buffer.reserve(1024);
}

zgles2_render::zgles2_render(const iresource* resource) :
    irender(resource),
    m_data(new data())
{
}

zgles2_render::~zgles2_render()
{
}

void zgles2_render::init(int width, int height)
{
    std::cout << "zgles2_render::init() " << width << ", " << height << std::endl;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    load_shaders(get_resource());
}

void zgles2_render::deinit()
{
    std::cout << "zgles2_render::deinit()" << std::endl;

    if (m_data->program) {
        glDeleteProgram(m_data->program);
        m_data->program = 0;
    }
}

void zgles2_render::render(const imodel* model, const zvec2& position)
{
    const auto geom = model->get_geometry();
    const auto color = model->get_color();
    const auto layer = model->get_layer();

    for(size_t i = 0; i < geom.size(); i++) {
        const zvec2 result = geom[i] + position;
        m_data->buffer.push_back(result.x);
        m_data->buffer.push_back(result.y);
        m_data->buffer.push_back(layer);
    }

    // Load the vertex data
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, m_data->buffer.data() );
    glEnableVertexAttribArray( 0 );
    glUniform3f( m_data->prog_color, color.r, color.g, color.b );
    const int size = static_cast<int>( m_data->buffer.size() / 3 );
    glDrawArrays( GL_TRIANGLES, 0,  size);

    m_data->buffer.resize(0);
}

void zgles2_render::render()
{
    //std::cout << "render" << std::endl;

    glClearColor(m_data->background_color.r, m_data->background_color.g, m_data->background_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the program object
    glUseProgram(m_data->program);
}

void zgles2_render::set_background_color(const zcolor& color)
{
    m_data->background_color = color;
}

bool zgles2_render::load_shaders(const iresource* resource)
{
    const auto vShaderStr = resource->get_text_resource("v.glsl");
    const auto fShaderStr = resource->get_text_resource("f.glsl");

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = load_shader_impl( GL_VERTEX_SHADER, (const char*) vShaderStr.data() );
    fragmentShader = load_shader_impl( GL_FRAGMENT_SHADER,  (const char*) fShaderStr.data() );

    // Create the program object
    programObject = glCreateProgram ( );

    if ( programObject == 0 ) {
        return 0;
    }

    glAttachShader( programObject, vertexShader );
    glAttachShader( programObject, fragmentShader );

    // Bind vPosition to attribute 0
    glBindAttribLocation( programObject, 0, "vPosition" );

    // Link the program
    glLinkProgram( programObject );

    // Check the link status
    glGetProgramiv( programObject, GL_LINK_STATUS, &linked );

    if( !linked ) {
        GLint infoLen = 0;

        glGetProgramiv( programObject, GL_INFO_LOG_LENGTH, &infoLen );

        if( infoLen > 1 )
        {
            char* infoLog = (char*) malloc (sizeof(char) * infoLen );

            glGetProgramInfoLog( programObject, infoLen, NULL, infoLog );
            std::cerr << "Error linking program:\n" << infoLog << std::endl;

            free( infoLog );
        }
        glDeleteProgram( programObject );
        return false;
    }

    // Store the program object
    m_data->program = programObject;
    m_data->prog_color = glGetUniformLocation( programObject, "vColor" );

    return true;
}

namespace {
    GLuint load_shader_impl( GLenum type, const char *shaderSrc )
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
}
