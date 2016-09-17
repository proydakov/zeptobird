#include <cmath>
#include <algorithm>

#include "zsingle_scale_animation.h"

namespace  {
    const float SCALE_FACTOR = 200.0f;
}

zsingle_scale_animation::zsingle_scale_animation(zfloat max) :
    m_max(max),
    m_time(M_PI * SCALE_FACTOR),
    m_scale(1)
{
}

zsingle_scale_animation::~zsingle_scale_animation()
{
}

void zsingle_scale_animation::update(ztime ms)
{
    m_time += ms;
    float angle = m_time / SCALE_FACTOR;
    angle = std::min(angle, static_cast<float>(M_PI));
    m_scale = (std::sin( angle ) + 1) / 2 * (m_max - 1) + 1;
}

zfloat zsingle_scale_animation::get_scale() const
{
    return m_scale;
}

zfloat zsingle_scale_animation::get_rotation() const
{
    return 0;
}

zvec2 zsingle_scale_animation::get_position() const
{
    return zvec2{0, 0};
}

void zsingle_scale_animation::restart()
{
    m_time = 0;
}
