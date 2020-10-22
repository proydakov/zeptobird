#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <type_traits>

#include <math/zmath.h>
#include <common/ztypes.h>
#include <render/irenderable.h>

#include <platform/iresource.h>

#include "zgles2.h"
#include "zgles2_render.h"
#include "zgles2_program.h"
#include "zgles2_texture.h"

namespace {

struct color_vertex
{
    zfloat position[3];
    zfloat color   [3];
};

struct texture_vertex
{
    zfloat position[3];
    zfloat texture [2];
};

}

struct zgles2_render::data
{
    data(const iresource&);

    const iresource& resource;

    zmat44 mvp;

    int view_width;
    int view_height;

    int scene_width;
    int scene_height;

    bool scene_change_notify;
    std::function<void(const zsize&)> scene_change_callback;

    std::vector<color_vertex> geom_buffer;
    std::vector<color_vertex> aabb_buffer;
    std::vector<texture_vertex> text_buffer;

    size_t vertex_statistic;

    zcolor background_color;
    zcolor aabb_color;
    bool   aabb_visible;

    zgles2_program model_program;
    zgles2_program widget_program;

    zgles2_texture alphabet_texture;
};

zgles2_render::data::data(const iresource& resource) :
    resource(resource)
{
    view_width = 1;
    view_height = 1;

    scene_width = 1;
    scene_height = 1;

    scene_change_notify = false;

    geom_buffer.reserve(1024 * 32);
    aabb_buffer.reserve(1024 * 32);
    text_buffer.reserve(1024 * 32);

    vertex_statistic = 0;

    background_color = {1.0f, 1.0f, 1.0f};
    aabb_color = {1.0f, 1.0f, 1.0f};
    aabb_visible = false;
}

zgles2_render::zgles2_render(const iresource& resource) :
    m_data(new data(resource))
{
    std::cout << "zgles2_render()" << std::endl;

    load_shaders(m_data->resource);
    load_textures(m_data->resource);
}

zgles2_render::~zgles2_render()
{
    // remove text
    m_data->alphabet_texture.unload();

    // remove programs
    m_data->model_program.unload();
    m_data->widget_program.unload();
    
    std::cout << "~zgles2_render()" << std::endl;
}

void zgles2_render::resize(const zsize& view_size)
{
    const int width = view_size.width;
    const int height = view_size.height;

    std::cout << "zgles2_render::resize() " << width << ", " << height << std::endl;

    m_data->view_width  = width;
    m_data->view_height = height;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    update_mvp();
}

void zgles2_render::render(const irenderable& object, const zvec2& pos, zfloat rot, zfloat scale)
{
    /// @todo : test vbo impl

    zmat33 mtranslate = ztranslate3(pos);
    zmat33 mrotate = zrotate_around_z3(rot);
    zmat33 mscale = zscale3(scale, scale);
    zmat33 mtransform = zmul(zmul(mtranslate, mrotate), mscale);

    const float layer = object.get_layer();
    // AABB
    if(m_data->aabb_visible)
    {
        const auto& aabb_color = m_data->aabb_color;
        const auto& aabb = object.get_aabb_geom();
        for(size_t i = 0 ; i < aabb.size(); i++) {
            const zvec3 src(aabb[i].x, aabb[i].y, 1);
            const zvec3 result = zmul(mtransform, src);
            m_data->aabb_buffer.push_back(color_vertex({{result.x, result.y, layer + 0.1f}, {aabb_color.r, aabb_color.g, aabb_color.b}}));
        }
    }
    // GEOM
    {
        const auto& color = object.get_color();
        const auto& geom = object.get_colored_geom();
        for(size_t i = 0; i < geom.size(); i++) {
            const zvec3 src(geom[i].x, geom[i].y, 1);
            const zvec3 result = zmul(mtransform, src);
            m_data->geom_buffer.push_back(color_vertex({{result.x, result.y, layer + 0.00f}, {color.r, color.g, color.b}}));
        }
    }
    // TEXTURED
    {
        const auto& geom = object.get_textured_geom();
        const auto& coord = object.get_textured_coord();
        for(size_t i = 0 ; i < geom.size(); i++) {
            const zvec3 src(geom[i].x, geom[i].y, 1);
            const zvec3 result = zmul(mtransform, src);
            m_data->text_buffer.push_back(texture_vertex({{result.x, result.y, layer + 0.3f}, {coord[i].x, coord[i].y}}));
        }
    }
}

static_assert( sizeof(GLfloat) == sizeof(zfloat), "invalid float size for shader" );

void zgles2_render::render()
{
    /// @todo : test vbo impl

    glClearColor(m_data->background_color.r, m_data->background_color.g, m_data->background_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_data->vertex_statistic = 0;

    // render objects
    {
        glUseProgram(m_data->model_program.get_id());

        glUniformMatrix4fv(m_data->model_program.get_uniform_location("vMVP"), 1, GL_FALSE, (GLfloat*)(&m_data->mvp));

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
        if(!m_data->aabb_buffer.empty())
        {
            glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, sizeof(color_vertex), &m_data->aabb_buffer[0].position);
            glVertexAttribPointer(vColorAttr, 3, GL_FLOAT, GL_TRUE, sizeof(color_vertex), &m_data->aabb_buffer[0].color);
            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(m_data->aabb_buffer.size()));
        }

        glDisableVertexAttribArray(vPositionAttr);
        glDisableVertexAttribArray(vPositionAttr);

        m_data->vertex_statistic += m_data->aabb_buffer.size();
        m_data->vertex_statistic += m_data->geom_buffer.size();

        m_data->aabb_buffer.resize(0);
        m_data->geom_buffer.resize(0);
    }

    // render ui text
    {
        glUseProgram(m_data->widget_program.get_id());

        glUniformMatrix4fv(m_data->widget_program.get_uniform_location("vMVP"), 1, GL_FALSE, (GLfloat*)(&m_data->mvp));

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

        glDisableVertexAttribArray(vPositionAttr);
        glDisableVertexAttribArray(vTexCoordAttr);

        m_data->vertex_statistic += m_data->text_buffer.size();

        m_data->text_buffer.resize(0);
    }
    glUseProgram(0);
}

void zgles2_render::set_scene_size(const zsize& scene_size)
{
    m_data->scene_width = scene_size.width;
    m_data->scene_height = scene_size.height;
    if(m_data->scene_change_notify) {
        m_data->scene_change_callback(scene_size);
    }
    update_mvp();
}

void zgles2_render::set_background_color(const zcolor& color)
{
    m_data->background_color = color;
}

void zgles2_render::set_aabb_color(const zcolor& color)
{
    m_data->aabb_color = color;
}

void zgles2_render::set_aabb_visible(bool visible)
{
    m_data->aabb_visible = visible;
}

zvec2 zgles2_render::view_2_scene(const zvec2& view)
{
    return zunproject(m_data->mvp, zvec4{0, 0, 1.0f * m_data->view_width, 1.0f * m_data->view_height}, view);
}

void zgles2_render::set_scene_size_change_callback(const std::function<void(const zsize&)>& functor)
{
    m_data->scene_change_notify = true;
    m_data->scene_change_callback = functor;
}

size_t zgles2_render::get_vertex_statistic() const
{
    return m_data->vertex_statistic;
}

void zgles2_render::update_mvp()
{
    const GLfloat hk = 1.0f * m_data->scene_height / m_data->view_height;
    const GLfloat wk = 1.0f * m_data->scene_width / m_data->view_width;

    GLfloat left   = -100;
    GLfloat right  = +100;
    GLfloat bottom = -100;
    GLfloat top    = +100;

    if(wk < hk) {
        const GLfloat k = hk / wk;
        left  = -1.0 * m_data->scene_width / 2 * k;
        right = +1.0 * m_data->scene_width / 2 * k;
        bottom = -1.0 * m_data->scene_height / 2;
        top    = +1.0 * m_data->scene_height / 2;
    }
    else {
        const GLfloat k = wk / hk;
        left  = -1.0 * m_data->scene_width / 2;
        right = +1.0 * m_data->scene_width / 2;
        bottom = -1.0 * m_data->scene_height / 2 * k;
        top    = +1.0 * m_data->scene_height / 2 * k;
    }

    zmat44 orto(zortho( left, right, bottom, top, +1000.0, -1000.0 ));
    zmat44 model_view;
    model_view.set_identity();
    m_data->mvp = zmul(orto, model_view);
}

bool zgles2_render::load_shaders(const iresource& resource)
{
    bool const load_model = m_data->model_program.load(resource, "shader/model_vertex.glsl", "shader/model_fragment.glsl",
                                           std::vector<std::string>{ "vPosition",  "vColor" },
                                           std::vector<std::string>{ "vMVP" });

    assert(load_model);

    bool const load_widget = m_data->widget_program.load(resource, "shader/widget_vertex.glsl", "shader/widget_fragment.glsl",
                                        std::vector<std::string>{ "vPosition",  "vTexCoord" },
                                        std::vector<std::string>{ "vMVP", "fTexture" });

    assert(load_widget);

    return (load_model && load_widget);
}

bool zgles2_render::load_textures(const iresource& resource)
{
    const size_t alphabet_width = 128;
    const size_t alphabet_height = 128;
    const size_t alphabet_length(alphabet_width * alphabet_height);

    std::string alphabet = resource.get_text_resource("data/alphabet.txt");

    auto it = std::remove(alphabet.begin(), alphabet.end(), '\n');
    alphabet.erase(it, alphabet.end());

    std::cout << "loaded alphabet size: " << alphabet.size() << std::endl;

    assert(alphabet_length == alphabet.size());

    GLubyte pixels[alphabet_length * 3];
    for(size_t i = 0, p = 0; i < alphabet_length; i++, p += 3) {
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
    bool const load = m_data->alphabet_texture.load(alphabet_width, alphabet_height, &pixels);

    /*
    // 2x2 Image, 3 bytes per pixel (R, G, B)
    GLubyte pixels[4 * 3] =
    {
        255,   0,   0, // Red
        0,   255,   0, // Green
        0,     0, 255, // Blue
        255, 255,   0  // Yellow2
    };
    bool load = m_data->alphabet_texture.load(2, 2, &pixels);
    */

    return load;
}
