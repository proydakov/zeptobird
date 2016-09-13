#pragma once

#include <math/zvec2.h>

struct zmat22
{
    zmat22();
    zmat22(const zvec2& c1, const zvec2& c2);

    void set_zero();
    void set_identity();

    zvec2 ex, ey;
};

zvec2 zmul(const zmat22& A, const zvec2& v);
zmat22 zmul(const zmat22& A, const zmat22& B);
