#include <cmath>

#include "zscale_animation.h"

namespace  {
    const float SCALE_FACTOR = 200.0f;
}

zscale_animation::zscale_animation(zfloat max) :
    m_max(max),
    m_time(0),
    m_scale(1)
{
}

zscale_animation::~zscale_animation()
{
}

void zscale_animation::update(ztime ms)
{
    m_time += ms;
    m_scale = (std::sin( m_time / SCALE_FACTOR ) + 1) / 2 * (m_max - 1) + 1;
}

zfloat zscale_animation::get_scale() const
{
    return m_scale;
}

zfloat zscale_animation::get_rotation() const
{
    return 0;
}

zvec2 zscale_animation::get_position() const
{
    return zvec2{0, 0};
}
