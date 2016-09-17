#include "zmodel.h"

zmodel::zmodel(const std::vector<zvec2>& geom,
               const std::vector<zvec2>& aabb,
               const zcolor& color, int layer) :
    m_geom(geom),
    m_aabb(aabb),
    m_color(color),
    m_layer(layer),
    m_rotation(0),
    m_scale(1)
{
}

zmodel::~zmodel()
{
}

int zmodel::get_layer() const
{
    return m_layer;
}

const std::vector<zvec2>& zmodel::get_colored_geom() const
{
    return m_geom;
}

const std::vector<zvec2>& zmodel::get_aabb_geom() const
{
    return m_aabb;
}

const zcolor& zmodel::get_color() const
{
    return m_color;
}

const std::vector<zvec2>& zmodel::get_textured_geom() const
{
    return m_textured_geom;
}

const std::vector<zvec2>& zmodel::get_textured_coord() const
{
    return m_textured_coord;
}

const std::string& zmodel::get_texture_name() const
{
    return m_texture_name;
}

std::vector<zvec2>& zmodel::get_geom_ref()
{
    return m_geom;
}

std::vector<zvec2>& zmodel::get_aabb_ref()
{
    return m_aabb;
}

zfloat zmodel::get_rotation() const
{
    return m_rotation;
}

void zmodel::set_rotation(zfloat rotation)
{
    m_rotation = rotation;
}

zfloat zmodel::get_scale() const
{
    return m_scale;
}

void zmodel::set_scale(zfloat scale)
{
    m_scale = scale;
}
