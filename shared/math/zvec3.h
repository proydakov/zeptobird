#pragma once

#include <ostream>
#include <common/ztypes.h>

struct zvec3
{
    zvec3();
    zvec3(zfloat x_, zfloat y_, zfloat z_);

    void set_zero();

    void set(zfloat x_, zfloat y_, zfloat z_);

    zvec3 operator -() const;

    void operator += (const zvec3& v);

    void operator -= (const zvec3& v);

    void operator *= (zfloat s);

    void operator /= (zfloat a);

    zfloat x, y, z;
};

zvec3 operator * (zfloat s, const zvec3& a);
zvec3 operator + (const zvec3& a, const zvec3& b);
zvec3 operator - (const zvec3& a, const zvec3& b);

std::ostream& operator<< (std::ostream& stream, const zvec3& vec);
