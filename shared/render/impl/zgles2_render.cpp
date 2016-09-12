#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

#include <math/zmath.h>

#include <render/types.h>
#include <render/imodel.h>
#include <render/iwidget.h>

#include <platform/iresource.h>

#include "zgles2.h"
#include "zgles2_render.h"
#include "zgles2_program.h"
#include "zgles2_texture.h"

struct zgles2_render::data
{
    data();

    int view_width;
    int view_height;
    float view_angle;

    int scene_width;
    int scene_height;

    std::vector<color_vertex> geom_buffer;
    std::vector<color_vertex> aabb_buffer;

    std::vector<texture_vertex> text_buffer;

    zcolor background_color;
    zcolor aabb_color;

    zgles2_program model_program;
    zgles2_program widget_program;

    zgles2_texture alphabet_texture;

    bool flag;
};

zgles2_render::data::data()
{
    view_width = 1;
    view_height = 1;
    view_angle = 0;

    scene_width = 1;
    scene_height = 1;

    geom_buffer.reserve(1024);
    aabb_buffer.reserve(1024);
    text_buffer.reserve(1024);

    background_color = {1.0f, 1.0f, 1.0f};
    aabb_color = {1.0f, 1.0f, 1.0f};

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
    load_textures(get_resource());
}

void zgles2_render::deinit()
{
    std::cout << "zgles2_render::deinit()" << std::endl;

    // remove text
    m_data->alphabet_texture.unload();

    // remove programs
    m_data->model_program.unload();
    m_data->widget_program.unload();
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
            m_data->aabb_buffer.push_back(color_vertex({result.x, result.y, layer + 0.01f, aabb_color.r, aabb_color.g, aabb_color.b}));
        }
    }
    {
        const auto& color = model->get_color();
        const auto geom = model->get_geom();
        for(size_t i = 0; i < geom.size(); i++) {
            const zvec2 result = geom[i] + position;
            m_data->geom_buffer.push_back(color_vertex({result.x, result.y, layer + 0.00f, color.r, color.g, color.b}));
        }
    }
}

void zgles2_render::render(const iwidget* widget, const zvec2& position, zfloat scale)
{
    /// @todo : test vbo impl

    const auto layer = widget->get_layer();
    // geom AABB
    {
        const auto& aabb_color = m_data->aabb_color;
        const auto aabb = widget->get_aabb();
        for(size_t i = 0 ; i < aabb.size(); i++) {
            const zvec2 result = aabb[i] + position;
            m_data->aabb_buffer.push_back(color_vertex({result.x, result.y, layer + 0.01f, aabb_color.r, aabb_color.g, aabb_color.b}));
        }
    }
    // geom
    {
        const auto& color = widget->get_color();
        const auto geom = widget->get_geom();
        for(size_t i = 0; i < geom.size(); i++) {
            const zvec2 result = geom[i] + position;
            m_data->geom_buffer.push_back(color_vertex({result.x, result.y, layer + 0.00f, color.r, color.g, color.b}));
        }
    }
    // texture
    {
        const auto geom = widget->get_textured_geom();
        const auto coord = widget->get_textured_coord();
        for(size_t i = 0 ; i < geom.size(); i++) {
            const zvec2 result = geom[i] + position;
            m_data->text_buffer.push_back(texture_vertex({result.x, result.y, layer + 0.01f, coord[i].x, coord[i].y}));
        }
    }
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

    // render objects
    {
        glUseProgram(m_data->model_program.get_id());

        glUniformMatrix4fv(m_data->model_program.get_uniform_location("vProjection"), 1, GL_FALSE, orto.data());
        glUniformMatrix4fv(m_data->model_program.get_uniform_location("vModelView"), 1, GL_FALSE, model_view.data());

        const int vPositionAttr = m_data->model_program.get_attribute_location("vPosition");
        const int vColorAttr = m_data->model_program.get_attribute_location("vColor");

        glEnableVertexAttribArray(vPositionAttr);
        glEnableVertexAttribArray(vColorAttr);

        // draw model
        {
            glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, sizeof(color_vertex), &m_data->geom_buffer[0].position);
            glVertexAttribPointer(vColorAttr, 3, GL_FLOAT, GL_TRUE, sizeof(color_vertex), &m_data->geom_buffer[0].color);
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_data->geom_buffer.size()));
        }

        // draw aabb
        {
            glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, sizeof(color_vertex), &m_data->aabb_buffer[0].position);
            glVertexAttribPointer(vColorAttr, 3, GL_FLOAT, GL_TRUE, sizeof(color_vertex), &m_data->aabb_buffer[0].color);
            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_data->aabb_buffer.size()));
        }

        m_data->geom_buffer.resize(0);
        m_data->aabb_buffer.resize(0);
    }

    // render ui text
    {
        glUseProgram(m_data->widget_program.get_id());

        glUniformMatrix4fv(m_data->widget_program.get_uniform_location("vProjection"), 1, GL_FALSE, orto.data());
        glUniformMatrix4fv(m_data->widget_program.get_uniform_location("vModelView"), 1, GL_FALSE, model_view.data());

        const int vPositionAttr = m_data->widget_program.get_attribute_location("vPosition");
        const int vTexCoordAttr = m_data->widget_program.get_attribute_location("vTexCoord");

        glEnableVertexAttribArray(vPositionAttr);
        glEnableVertexAttribArray(vTexCoordAttr);

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, m_data->alphabet_texture.get_id() );

        glUniform1i( m_data->widget_program.get_uniform_location("fTexture"), 0 );

        glVertexAttribPointer( vPositionAttr, 3, GL_FLOAT, GL_FALSE, sizeof(texture_vertex), &m_data->text_buffer[0].position);
        glVertexAttribPointer( vTexCoordAttr, 2, GL_FLOAT, GL_TRUE, sizeof(texture_vertex), &m_data->text_buffer[0].texture);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_data->text_buffer.size()));

        m_data->text_buffer.resize(0);
    }
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
    bool load = m_data->model_program.load(resource, "model_vertex.glsl", "model_fragment.glsl",
                                           std::vector<std::string>{ "vPosition",  "vColor" },
                                           std::vector<std::string>{ "vModelView", "vProjection" });

    assert(load);

    load *= m_data->widget_program.load(resource, "widget_vertex.glsl", "widget_fragment.glsl",
                                        std::vector<std::string>{ "vPosition",  "vTexCoord" },
                                        std::vector<std::string>{ "vModelView", "vProjection", "fTexture" });

    assert(load);

    return (load);
}

bool zgles2_render::load_textures(const iresource* resource)
{
    const size_t alphabet_width = 128;
    const size_t alphabet_height = 128;
    const size_t alphabet_length(alphabet_width * alphabet_height);

    std::string alphabet = resource->get_text_resource("alphabet.txt");

    auto it = std::remove(alphabet.begin(), alphabet.end(), '\n');
    alphabet.erase(it, alphabet.end());

    std::cout << "loaded alphabet size: " << alphabet.size() << std::endl;

    assert(alphabet_length == alphabet.size());

    GLubyte pixels[alphabet_length * 3];
    for(int i = 0, p = 0; i < alphabet_length; i++, p += 3) {
        switch(alphabet[i]) {
            case '+':
            case '*':
            case '-':
            case '|':
            case '/':
            case '\\':
                pixels[p + 0] = 255;
                pixels[p + 1] = 255;
                pixels[p + 2] = 255;
                break;

            default:
                pixels[p + 0] = 0;
                pixels[p + 1] = 0;
                pixels[p + 2] = 0;
                break;
        }
    }
    bool load = m_data->alphabet_texture.load(alphabet_width, alphabet_height, &pixels);

    /*
    // 2x2 Image, 3 bytes per pixel (R, G, B)
    GLubyte pixels[4 * 3] =
    {
        255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
        255, 255,   0  // Yellow2
    };
    bool load = m_data->alphabet_texture.load(2, 2, &pixels);
    */

    return load;
}
