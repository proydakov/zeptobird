#include "zmodel.h"

zmodel::zmodel(const std::vector<zvec2>& geometry,
               const std::vector<zvec2>& aabb,
               const zcolor& color, int layer) :
    m_geometry(geometry),
    m_aabb(aabb),
    m_color(color),
    m_layer(layer)
{
}

zmodel::~zmodel()
{
}

const std::vector<zvec2>& zmodel::get_geometry() const
{
    return m_geometry;
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
