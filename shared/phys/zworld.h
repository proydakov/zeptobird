#pragma once

#include <vector>

#include <math/zmath.h>
#include <phys/ibody.h>
#include <phys/zbody_def.h>

class zworld
{
public:
    zworld(const zvec2& gravity);

    ibody* create_body(const zbody_def& def) const;

    void add_body(ibody* body);
    void remove_body(ibody* body);

    void set_hero(ibody* hero);

    void update(size_t ms);

private:
    bool check_collided(const ibody* b1, const ibody* b2) const;
    bool check_circle_and_rect_collided(const ibody* b1, const ibody* b2) const;
    bool check_circle_and_circle_collided(const ibody* b1, const ibody* b2) const;

private:
    const zvec2 m_gravity;
    std::vector<ibody*> m_bodys;
    ibody* m_hero;
};
