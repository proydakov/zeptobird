#include "zrect_body.h"

zrect_body::zrect_body(zfloat width, zfloat height) :
    ibody(zbody_def::btype::rect),
    m_width(width),
    m_height(height)
{
}

zrect_body::~zrect_body()
{
}

zaabb zrect_body::get_aabb() const
{
    zaabb aabb{ get_position(), zvec2(m_width / 2, m_height / 2) };
    return aabb;
}

void zrect_body::set_size(zfloat width, zfloat height)
{
    m_width = width;
    m_height = height;
}

zfloat zrect_body::get_width() const
{
    return m_width;
}

zfloat zrect_body::get_height() const
{
    return m_height;
}
