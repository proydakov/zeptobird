#include "zcircle_body.h"

zcircle_body::zcircle_body(zfloat radius) :
    m_radius(radius)
{
}

zcircle_body::~zcircle_body()
{
}

zbody_def::btype zcircle_body::get_type() const
{
    return zbody_def::btype::circle;
}

zfloat zcircle_body::get_radius() const
{
    return m_radius;
}
