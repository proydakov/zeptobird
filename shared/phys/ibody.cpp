#include "ibody.h"

ibody::ibody(zbody_def::btype type) :
    m_type(type),
    m_active(true),
    m_collided(nullptr)
{
    m_position.set_zero();
    m_speed.set_zero();
}

ibody::~ibody()
{
}

zbody_def::btype ibody::get_type() const
{
    return m_type;
}

void ibody::set_position(const zvec2& position)
{
    m_position = position;
}

const zvec2& ibody::get_position() const
{
    return m_position;
}

void ibody::set_speed(const zvec2& speed)
{
    m_speed = speed;
}

const zvec2& ibody::get_speed() const
{
    return m_speed;
}

void ibody::set_active(bool active)
{
    m_active = active;
}

bool ibody::get_active() const
{
    return m_active;
}

void ibody::set_collided(ibody* collided)
{
    m_collided = collided;
}

ibody* ibody::get_collided() const
{
    return m_collided;
}
