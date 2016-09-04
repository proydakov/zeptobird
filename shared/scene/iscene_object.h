#pragma once

#include <math/zmath.h>

class irender;

class iscene_object
{
public:
    iscene_object();
    virtual ~iscene_object();

    virtual void update(size_t ms) = 0;
    virtual void render(irender* render) const = 0;

    virtual const zvec2& get_position() const = 0;
    virtual void set_position(const zvec2& position) = 0;
};
