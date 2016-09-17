#pragma once

#include <math/zmath.h>
#include <common/ztime.h>
#include <common/ztypes.h>

class ianimation
{
public:
    virtual ~ianimation();

    virtual void update(ztime ms) = 0;

    virtual zfloat get_scale()    const = 0;
    virtual zfloat get_rotation() const = 0;
    virtual zvec2  get_position() const = 0;
};
