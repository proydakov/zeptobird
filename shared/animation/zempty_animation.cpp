#include "zempty_animation.h"

zempty_animation::zempty_animation()
{
}

zempty_animation::~zempty_animation()
{
    int i = 0;
}

void zempty_animation::update(ztime ms)
{
}

zfloat zempty_animation::get_scale() const
{
    return 1;
}

zfloat zempty_animation::get_rotation() const
{
    return 0;
}

zvec2 zempty_animation::get_position() const
{
    return zvec2{0, 0};
}
