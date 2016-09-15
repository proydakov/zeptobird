#pragma once

#include <ostream>
#include <common/ztypes.h>

struct zvec4
{
    zvec4();
    zvec4(zfloat x_, zfloat y_, zfloat z_, zfloat w_);

    void set_zero();

    void set(zfloat x_, zfloat y_, zfloat z_, zfloat w_);

    zvec4 operator -() const;

    void operator += (const zvec4& v);

    void operator -= (const zvec4& v);

    void operator *= (zfloat s);

    void operator /= (zfloat a);

    zfloat x, y, z, w;
};

zvec4 operator * (zfloat s, const zvec4& a);
zvec4 operator + (const zvec4& a, const zvec4& b);
zvec4 operator - (const zvec4& a, const zvec4& b);

std::ostream& operator<< (std::ostream& stream, const zvec4& vec);
