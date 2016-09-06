#include "zrect_body.h"

zrect_body::zrect_body(zfloat width, zfloat height) :
    m_width(width),
    m_height(height)
{
}

zrect_body::~zrect_body()
{
}

zbody_def::btype zrect_body::get_type() const
{
    return zbody_def::btype::rect;
}

zaabb zrect_body::get_aabb() const
{
    zaabb aabb{ get_position(), zvec2(m_width / 2, m_height / 2) };
    return aabb;
}

zfloat zrect_body::get_width() const
{
    return m_width;
}

zfloat zrect_body::get_height() const
{
    return m_height;
}
