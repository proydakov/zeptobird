#pragma once

#include <math/zmath.h>
#include <phys/zaabb.h>
#include <phys/zbody_def.h>

class ibody
{
public:
    ibody();
    virtual ~ibody();

    virtual zbody_def::btype get_type() const = 0;
    virtual zaabb get_aabb() const = 0;

    void set_position(const zvec2& position);
    const zvec2& get_position() const;

    void set_speed(const zvec2& speed);
    const zvec2& get_speed() const;

    void set_collided(bool flag);
    bool get_collided() const;

private:
    zvec2 m_position;
    zvec2 m_speed;
    bool  m_collided;
};
