#pragma once

#include <math/zmath.h>
#include <phys/zbody_def.h>

class ibody
{
public:
    ibody();
    virtual ~ibody();

    virtual zbody_def::btype get_type() const = 0;

    void set_position(const zvec2& position);
    const zvec2& get_position() const;
    zvec2& get_position();

    void set_collided(bool flag);
    bool get_collided() const;

private:
    zvec2 m_position;
    bool  m_collided;
};
