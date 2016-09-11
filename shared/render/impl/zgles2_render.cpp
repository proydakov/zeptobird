#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

#include <math/zmath.h>
#include <platform/iresource.h>
#include <render/imodel.h>
#include <render/iwidget.h>

#include "zgles2.h"
#include "zgles2_render.h"

namespace {
GLuint load_shader_impl(GLenum type, const char *shaderSrc);

struct model_vertex
{
    GLfloat position[3];
    GLfloat color   [3];
};

}

struct zgles2_render::data
{
    data();

    int view_width;
    int view_height;
    float view_angle;

    int scene_width;
    int scene_height;

    std::vector<model_vertex> model_buffer;
    std::vector<model_vertex> aabb_buffer;

    zcolor background_color;
    zcolor aabb_color;

    GLuint program;
    int    position_attribute;
    int    color_attribute;
    int    model_view_uniform;
    int    projection_uniform;

    bool flag;
};

zgles2_render::data::data()
{
    view_width = 1;
    view_height = 1;
    view_angle = 0;

    scene_width = 1;
    scene_height = 1;

    model_buffer.reserve(1024);
    aabb_buffer.reserve(1024);

    background_color = {1.0f, 1.0f, 1.0f};
    aabb_color = {1.0f, 1.0f, 1.0f};

    program = 0;
    model_view_uniform = 0;
    projection_uniform = 0;

    flag = false;
}

zgles2_render::zgles2_render(const iresource* resource) :
    irender(resource),
    m_data(new data())
{
}

zgles2_render::~zgles2_render()
{
    deinit();
}

void zgles2_render::init(const zsize& view_size, float angle)
{
    const int width = view_size.width;
    const int height = view_size.height;

    std::cout << "zgles2_render::init() " << width << ", " << height << std::endl;

    m_data->view_width  = width;
    m_data->view_height = height;
    m_data->view_angle  = angle;

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
    /// @todo : test vbo impl
}

void zgles2_render::render(const imodel* model, const zvec2& position, zfloat scale)
{
    /// @todo : test vbo impl

    const auto layer = model->get_layer();
    {
        const auto& aabb_color = m_data->aabb_color;
        const auto aabb = model->get_aabb();
        for(size_t i = 0 ; i < aabb.size(); i++) {
            const zvec2 result = aabb[i] + position;
            m_data->aabb_buffer.push_back(model_vertex({result.x, result.y, layer + 0.01f, aabb_color.r, aabb_color.g, aabb_color.b}));
        }
    }
    {
        const auto& color = model->get_color();
        const auto geom = model->get_geom();
        for(size_t i = 0; i < geom.size(); i++) {
            const zvec2 result = geom[i] + position;
            m_data->model_buffer.push_back(model_vertex({result.x, result.y, layer + 0.00f, color.r, color.g, color.b}));
        }
    }
}

void zgles2_render::render(const iwidget* widget, const zvec2& position, zfloat scale)
{
    /// @todo : test vbo impl
}

void zgles2_render::render()
{
    /// @todo : test vbo impl

    glClearColor(m_data->background_color.r, m_data->background_color.g, m_data->background_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /// @todo : think how to improve
    assert(m_data->scene_width == m_data->scene_height);
    const GLfloat left  = -1.0 * m_data->scene_width / 2 * m_data->view_width / m_data->view_height;
    const GLfloat right = +1.0 * m_data->scene_width / 2 * m_data->view_width / m_data->view_height;
    const GLfloat bottom = -1.0 * m_data->scene_height / 2;
    const GLfloat top    = +1.0 * m_data->scene_height / 2;

    std::vector<GLfloat> orto(zortho_matrix<GLfloat>( left, right, bottom, top, +10.0, -10.0 ) );
    std::vector<GLfloat> model_view( zrotate_around_z_matrix<GLfloat>(m_data->view_angle * M_PI / 180) );

    // Use the program object
    glUseProgram(m_data->program);

    glUniformMatrix4fv(m_data->projection_uniform, 1, GL_FALSE, orto.data());
    glUniformMatrix4fv(m_data->model_view_uniform, 1, GL_FALSE, model_view.data());

    // draw model
    {
        glVertexAttribPointer(m_data->position_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(model_vertex), &m_data->model_buffer[0].position);
        glEnableVertexAttribArray(m_data->position_attribute);

        glVertexAttribPointer(m_data->color_attribute, 3, GL_FLOAT, GL_TRUE, sizeof(model_vertex), &m_data->model_buffer[0].color);
        glEnableVertexAttribArray(m_data->color_attribute);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_data->model_buffer.size()));
    }

    // draw aabb
    {
        glVertexAttribPointer(m_data->position_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(model_vertex), &m_data->aabb_buffer[0].position);
        glEnableVertexAttribArray(m_data->position_attribute);

        glVertexAttribPointer(m_data->color_attribute, 3, GL_FLOAT, GL_TRUE, sizeof(model_vertex), &m_data->aabb_buffer[0].color);
        glEnableVertexAttribArray(m_data->color_attribute);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_data->aabb_buffer.size()));
    }

    m_data->model_buffer.resize(0);
    m_data->aabb_buffer.resize(0);
}

void zgles2_render::set_scene_size(const zsize& view_size)
{
    m_data->scene_width = view_size.width;
    m_data->scene_height = view_size.height;
}

void zgles2_render::set_background_color(const zcolor& color)
{
    m_data->background_color = color;
}

void zgles2_render::set_aabb_color(const zcolor& color)
{
    m_data->aabb_color = color;
}

bool zgles2_render::load_shaders(const iresource* resource)
{
    const auto vShaderStr = resource->get_text_resource("model_vertex.glsl");
    const auto fShaderStr = resource->get_text_resource("model_fragment.glsl");

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = load_shader_impl( GL_VERTEX_SHADER, (const char*) vShaderStr.data() );
    fragmentShader = load_shader_impl( GL_FRAGMENT_SHADER,  (const char*) fShaderStr.data() );

    if(0 == vertexShader || 0 == fragmentShader) {
        return false;
    }

    // Create the program object
    programObject = glCreateProgram();

    if ( programObject == 0 ) {
        return 0;
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
    m_data->program = programObject;

    m_data->position_attribute = glGetAttribLocation(programObject, "vPosition");
    m_data->color_attribute = glGetAttribLocation(programObject, "vColor");

    m_data->model_view_uniform = glGetUniformLocation( programObject, "vModelView" );
    m_data->projection_uniform = glGetUniformLocation( programObject, "vProjection" );

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
