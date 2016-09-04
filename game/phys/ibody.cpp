#include "ibody.h"

ibody::ibody() :
    m_collided(false)
{
    m_position.set_zero();
}

ibody::~ibody()
{
}

void ibody::set_position(const zvec2& position)
{
    m_position = position;
}

const zvec2& ibody::get_position() const
{
    return m_position;
}

zvec2& ibody::get_position()
{
    return m_position;
}

void ibody::set_collided(bool flag)
{
    m_collided = flag;
}

bool ibody::get_collided() const
{
    return m_collided;
}
