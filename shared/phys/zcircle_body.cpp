#include "zcircle_body.h"

zcircle_body::zcircle_body(zfloat radius) :
    ibody(zbody_def::btype::circle),
    m_radius(radius)
{
}

zcircle_body::~zcircle_body()
{
}

zaabb zcircle_body::get_aabb() const
{
    zaabb aabb{ get_position(), zvec2(m_radius, m_radius) };
    return aabb;
}

zfloat zcircle_body::get_radius() const
{
    return m_radius;
}
