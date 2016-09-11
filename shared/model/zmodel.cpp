#include "zmodel.h"

zmodel::zmodel(const std::vector<zvec2>& geom,
               const std::vector<zvec2>& aabb,
               const zcolor& color, int layer) :
    m_geom(geom),
    m_aabb(aabb),
    m_color(color),
    m_layer(layer)
{
}

zmodel::~zmodel()
{
}

const std::vector<zvec2>& zmodel::get_geom() const
{
    return m_geom;
}

const std::vector<zvec2>& zmodel::get_aabb() const
{
    return m_aabb;
}

const zcolor& zmodel::get_color() const
{
    return m_color;
}

int zmodel::get_layer() const
{
    return m_layer;
}

std::vector<zvec2>& zmodel::get_geom_ref()
{
    return m_geom;
}

std::vector<zvec2>& zmodel::get_aabb_ref()
{
    return m_aabb;
}