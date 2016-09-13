#pragma once

#include <math/zvec2.h>
#include <math/zvec3.h>

struct zmat33
{
    zmat33();
    zmat33(const zvec3& c1, const zvec3& c2, const zvec3& c3);

    void set_zero();
    void set_identity();

    zvec3 ex, ey, ez;
};

zvec3 zmul(const zmat33& A, const zvec3& v);
zmat33 zmul(const zmat33& A, const zmat33& B);

zmat33 ztranslate(const zvec2& position);
zmat33 zrotate(zfloat rotation);
zmat33 zscale(zfloat scale);