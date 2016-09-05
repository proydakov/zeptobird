#include <cassert>

#include <vector>
#include <iostream>

#include <platform/iresource.h>
#include <render/imodel.h>

#include "zgles2.h"
#include "zgles2_render.h"

namespace {
    GLuint load_shader_impl( GLenum type, const char *shaderSrc );
    std::vector<GLfloat> load_ortho_matrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
}

struct zgles2_render::data
{
    data();

    int width;
    int height;

    std::vector<GLfloat> buffer;

    zcolor background_color;

    GLuint program;
    int    color_uniform;
    int    mvp_uniform;

    bool flag;
};

zgles2_render::data::data()
{
    width = 0;
    height = 0;

    buffer.reserve(1024);
    background_color = {1.0f, 1.0f, 1.0f};

    program = 0;
    color_uniform = 0;
    mvp_uniform = 0;

    flag = false;
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

    m_data->width = width;
    m_data->height = height;

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

void zgles2_render::prepare()
{
    glClearColor(m_data->background_color.r, m_data->background_color.g, m_data->background_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the program object
    glUseProgram(m_data->program);

    std::vector<GLfloat> orto{load_ortho_matrix( -2, 2,
                                                 -2 * (GLfloat) m_data->height / (GLfloat) m_data->width,
                                                  2 * (GLfloat) m_data->height / (GLfloat) m_data->width,
                                                 10.0, -10.0 )
    };

    glUniformMatrix4fv(m_data->mvp_uniform, 1, GL_FALSE, orto.data());
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

    glUniform3f( m_data->color_uniform, color.r, color.g, color.b );
    const int size = static_cast<int>( m_data->buffer.size() / 3 );

    glDrawArrays( GL_TRIANGLES, 0,  size);

    m_data->buffer.resize(0);
}

void zgles2_render::render()
{
    /// @todo : impl draw vbo
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
    programObject = glCreateProgram();

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
    m_data->program = programObject;
    m_data->color_uniform = glGetUniformLocation( programObject, "vColor" );
    m_data->mvp_uniform = glGetUniformLocation( programObject, "vMVP" );

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

    std::vector<GLfloat> load_ortho_matrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
    {
        std::vector<GLfloat> matrix(16, 0);

        GLfloat r_l = right - left;
        GLfloat t_b = top - bottom;
        GLfloat f_n = far - near;
        GLfloat tx = - (right + left) / (right - left);
        GLfloat ty = - (top + bottom) / (top - bottom);
        GLfloat tz = - (far + near) / (far - near);

        matrix[0] = 2.0f / r_l;
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = tx;

        matrix[4] = 0.0f;
        matrix[5] = 2.0f / t_b;
        matrix[6] = 0.0f;
        matrix[7] = ty;

        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = 2.0f / f_n;
        matrix[11] = tz;

        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = 1.0f;

        return matrix;
    }

}
