#include <cmath>

#include "zaabb.h"

zaabb::zaabb() :
    c(),
    r()
{
}

zaabb::zaabb(const zvec2& center, const zvec2& halfwidths) :
    c(center),
    r(halfwidths)
{
}

bool test_aabb_aabb_simd(const zaabb &a, const zaabb &b)
{
    // SIMD optimized AABB-AABB test
    // Optimized by removing conditional branches
    bool x = std::abs(a.c.x - b.c.x) <= (a.r.x + b.r.x);
    bool y = std::abs(a.c.y - b.c.y) <= (a.r.y + b.r.y);

    return x && y;
}
