#pragma once

#include <math/zmath.h>
#include <phys/zaabb.h>
#include <phys/zbody_def.h>

class ibody
{
public:
    ibody(zbody_def::btype type);
    virtual ~ibody();

    virtual zaabb get_aabb() const = 0;

    zbody_def::btype get_type() const;

    void set_position(const zvec2& position);
    const zvec2& get_position() const;

    void set_speed(const zvec2& speed);
    const zvec2& get_speed() const;

    void set_active(bool active);
    bool get_active() const;

    void set_collided(ibody* collided);
    ibody* get_collided() const;

private:
    zbody_def::btype m_type;

    zvec2  m_position;
    zvec2  m_speed;
    bool   m_active;
    ibody* m_collided;
};
