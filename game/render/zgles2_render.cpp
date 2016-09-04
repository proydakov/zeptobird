#include <iostream>

#include "gles2.h"
#include "zgles2_render.h"

#include <platform/iresource.h>

namespace {
    GLuint load_shader( GLenum type, const char *shaderSrc )
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

        if ( !compiled )
        {
            GLint infoLen = 0;
            glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

            if ( infoLen > 1 )
            {
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

struct zgles2_render::data
{
    GLuint m_program;
    int m_color;

    bool flag = false;
};

zgles2_render::zgles2_render() :
    m_data(new data())
{
}

zgles2_render::~zgles2_render()
{
}

void zgles2_render::init(const iresource* resource, int width, int height)
{
    std::cout << "zgles2_render_ctx::init() " << width << ", " << height << std::endl;

    if(0 == width || 0 == height) {
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    load_shaders(resource);
}

void zgles2_render::deinit()
{
    std::cout << "zgles2_render_ctx::release()" << std::endl;

    if (m_data->m_program) {
        glDeleteProgram(m_data->m_program);
        m_data->m_program = 0;
    }
}

void zgles2_render::render()
{
    //std::cout << "render" << std::endl;

    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the program object
    glUseProgram( m_data->m_program );

    {
        GLfloat vVertices[] = {
             0.0f,  0.0f, 0.0f,
            -0.9f, -0.9f, 0.0f,
             0.9f, -0.9f, 0.0f
        };

        // Load the vertex data
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
        glEnableVertexAttribArray ( 0 );

        if(m_data->flag) {
            glUniform3f( m_data->m_color, 1, 0, 0 );
        }
        else {
            glUniform3f( m_data->m_color, 0, 0, 1 );
        }

        glDrawArrays ( GL_TRIANGLES, 0, 3 );
    }

    {
        GLfloat vVertices[] = {
            0.0f, 1.0f, 0.0f,
           -0.9f, 0.1f, 0.0f,
            0.9f, 0.1f, 0.0f
        };

        // Load the vertex data
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
        glEnableVertexAttribArray ( 0 );

        if(m_data->flag) {
            glUniform3f( m_data->m_color, 0, 0, 1 );
        }
        else {
            glUniform3f( m_data->m_color, 1, 0, 0 );
        }

        glDrawArrays ( GL_TRIANGLES, 0, 3 );
    }
}

void zgles2_render::input()
{
    m_data->flag = !m_data->flag;
}

bool zgles2_render::load_shaders(const iresource* resource)
{
    const auto vShaderStr = resource->load_text_resource("v.glsl");
    const auto fShaderStr = resource->load_text_resource("f.glsl");

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = load_shader( GL_VERTEX_SHADER, (const char*) vShaderStr.data() );
    fragmentShader = load_shader( GL_FRAGMENT_SHADER,  (const char*) fShaderStr.data() );

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
    m_data->m_program = programObject;
    m_data->m_color = glGetUniformLocation( programObject, "vColor" );

    return true;
}
