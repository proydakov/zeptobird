#include "zmodel.h"

zmodel::zmodel(const std::vector<zvec2>& geometry, const zcolor& color, int layer) :
    m_geometry(geometry),
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

const zcolor& zmodel::get_color() const
{
    return m_color;
}

int zmodel::get_layer() const
{
    return m_layer;
}
