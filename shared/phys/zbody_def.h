#pragma once

#include <math/zmath.h>

struct zbody_def
{
    enum class btype {
        circle = 1,
        rect = 2
    };

    btype type;

    zfloat radius;
    zfloat width;
    zfloat height;
};
