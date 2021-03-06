#pragma once

#include <ostream>

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

zmat33 ztranslate3(const zvec2& position);
zmat33 zrotate_around_z3(zfloat rotation);
zmat33 zscale3(zfloat scalex, zfloat scaley);

std::ostream& operator<<(std::ostream& stream, const zmat33& mat);
