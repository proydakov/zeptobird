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

zfloat zrect_body::get_width() const
{
    return m_width;
}

zfloat zrect_body::get_height() const
{
    return m_height;
}
