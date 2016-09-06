#pragma once

#include <math/zmath.h>

struct zaabb
{
    zaabb();
    zaabb(const zvec2& center, const zvec2& halfwidths);

    zvec2 c;        // center point
    zvec2 r;        // halfwidths
};

bool test_AABB_AABB_SIMD(const zaabb &a, const zaabb &b);
