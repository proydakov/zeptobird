#pragma once

#include <math/zmath.h>
#include <common/ztime.h>

class irender;

class iscene_object
{
public:
    virtual ~iscene_object();

    virtual void update(ztime ms) = 0;
    virtual void render(irender* render) const = 0;

    virtual const zvec2& get_position() const = 0;
    virtual void set_position(const zvec2& position) = 0;

    virtual const zvec2& get_speed() const = 0;
    virtual void set_speed(const zvec2& speed) = 0;
};
