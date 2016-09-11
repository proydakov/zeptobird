#include "zwidget.h"

const std::string zwidget::m_texture_name = "alphabet";

zwidget::zwidget(int layer) :
    m_layer(layer),
    m_color{0, 0, 0},
    m_scale(1)
{
    m_position.set_zero();
}

zwidget::~zwidget()
{
}

const zvec2& zwidget::get_position() const
{
    return m_position;
}

void zwidget::set_position(const zvec2& position)
{
    m_position = position;
}

zfloat zwidget::get_scale() const
{
    return m_scale;
}

void zwidget::set_scale(zfloat scale)
{
    m_scale = scale;
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

std::vector<zvec2>& zwidget::get_geom_ref()
{
    return m_geom;
}

std::vector<zvec2>& zwidget::get_aabb()
{
    return m_aabb;
}

std::vector<zvec2>& zwidget::get_textured_geom()
{
    return m_textured_geom;
}

std::vector<zvec2>& zwidget::get_textured_coord()
{
    return m_textured_coord;
}
