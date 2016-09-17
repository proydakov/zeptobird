#include "zwidget.h"

#include <render/irender.h>
#include <animation/ianimation.h>
#include <animation/zempty_animation.h>

const std::string zwidget::m_texture_name = "alphabet";

zwidget::zwidget(int layer) :
    m_animator( new zempty_animation() ),
    m_visible(true),
    m_layer(layer),
    m_color{0, 0, 0},
    m_rotation(0),
    m_scale(1)
{
    m_position.set_zero();
}

zwidget::zwidget(int layer, std::unique_ptr<ianimation>&& animator) :
    m_animator( std::move(animator) ),
    m_visible(true),
    m_layer(layer),
    m_color{0, 0, 0},
    m_rotation(0),
    m_scale(1)
{
    m_position.set_zero();
}

zwidget::~zwidget()
{
}

void zwidget::update(ztime ms)
{
    m_animator->update(ms);
}

void zwidget::render(irender* render) const
{
    if(m_visible) {
        render->render(this, get_position(), get_rotation(), get_scale() * m_animator->get_scale());
    }
}


// apply animator
zrect zwidget::get_rect() const
{
    zrect rect = get_rect_impl();
    return rect;
    /*
     /// @todo : need resend event each update
    const zfloat scale = m_animator->get_scale();
    rect.min.x *= scale;
    rect.min.y *= scale;
    rect.max.x *= scale;
    rect.max.y *= scale;
    return rect;
     */
}

const zvec2& zwidget::get_position() const
{
    return m_position;
}

void zwidget::set_position(const zvec2& position)
{
    m_position = position;
}

zfloat zwidget::get_rotation() const
{
    return m_rotation;
}

void zwidget::set_rotation(zfloat rotation)
{
    m_rotation = rotation;
}

zfloat zwidget::get_scale() const
{
    return m_scale;
}

void zwidget::set_scale(zfloat scale)
{
    m_scale = scale;
}

void zwidget::set_visible(bool state)
{
    m_visible = state;
}

bool zwidget::get_visible() const
{
    return m_visible;
}

int zwidget::get_layer() const
{
    return m_layer;
}

const std::vector<zvec2>& zwidget::get_geom() const
{
    return m_geom;
}

const std::vector<zvec2>& zwidget::get_aabb() const
{
    return m_aabb;
}

const zcolor& zwidget::get_color() const
{
    return m_color;
}

const std::vector<zvec2>& zwidget::get_textured_geom() const
{
    return m_textured_geom;
}

const std::vector<zvec2>& zwidget::get_textured_coord() const
{
    return m_textured_coord;
}

const std::string& zwidget::get_texture_name() const
{
    return m_texture_name;
}

void zwidget::set_color(const zcolor& color)
{
    m_color = color;
}

std::vector<zvec2>& zwidget::get_geom_ref()
{
    return m_geom;
}

std::vector<zvec2>& zwidget::get_aabb_ref()
{
    return m_aabb;
}

std::vector<zvec2>& zwidget::get_textured_geom_ref()
{
    return m_textured_geom;
}

std::vector<zvec2>& zwidget::get_textured_coord_ref()
{
    return m_textured_coord;
}
