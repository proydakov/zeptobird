#pragma once

#include <ostream>

#include <math/zvec2.h>
#include <math/zvec3.h>
#include <math/zvec4.h>

struct zmat44
{
    zmat44();
    zmat44(const zvec4& c1, const zvec4& c2, const zvec4& c3, const zvec4& c4);

    void set_zero();
    void set_identity();

    zvec4 ex, ey, ez, ew;
};

zvec4 zmul(const zmat44& A, const zvec4& v);
zmat44 zmul(const zmat44& A, const zmat44& B);

zmat44 ztranslate4(const zvec3& position);
zmat44 zrotate_around_z4(zfloat rotation);
zmat44 zscale4(zfloat scalex, zfloat scaley, zfloat scalez);

zmat44 zortho(zfloat left, zfloat right, zfloat bottom, zfloat top, zfloat near, zfloat far);

bool zinvert4(const zmat44& src, zmat44& dst);
zvec2 zunproject(const zmat44& mvp, const zvec4& viewport, const zvec2& point);

std::ostream& operator<<(std::ostream& stream, const zmat44& mat);
