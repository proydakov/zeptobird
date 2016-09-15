#include "zvec4.h"

zvec4::zvec4()
{
}

zvec4::zvec4(zfloat x_, zfloat y_, zfloat z_, zfloat i_) : x(x_), y(y_), z(z_), i(i_)
{
}

void zvec4::set_zero()
{
    x = 0.0f; y = 0.0f; z = 0.0f;
}

void zvec4::set(zfloat x_, zfloat y_, zfloat z_, zfloat i_)
{
    x = x_; y = y_; z = z_; i_ = i;
}

zvec4 zvec4::operator -() const
{
    zvec4 v;
    v.set(-x, -y, -z, -i);
    return v;
}

void zvec4::operator += (const zvec4& v)
{
    x += v.x; y += v.y; z += v.z; i += v.i;
}

void zvec4::operator -= (const zvec4& v)
{
    x -= v.x; y -= v.y; z -= v.z; i -= v.i;
}

void zvec4::operator *= (zfloat s)
{
    x *= s; y *= s; z *= s; i *= s;
}

void zvec4::operator /= (zfloat a)
{
    x /= a; y /= a; z /= a; i /= a;
}

zvec4 operator * (zfloat s, const zvec4& a)
{
    return zvec4(s * a.x, s * a.y, s * a.z, s * a.i);
}

zvec4 operator + (const zvec4& a, const zvec4& b)
{
    return zvec4(a.x + b.x, a.y + b.y, a.z + b.z, a.i + b.i);
}

zvec4 operator - (const zvec4& a, const zvec4& b)
{
    return zvec4(a.x - b.x, a.y - b.y, a.z - b.z, a.i - b.i);
}

std::ostream& operator<< (std::ostream& stream, const zvec4& vec)
{
    stream << "[" << vec.x << ", " << vec.y  << ", " << vec.z << ", " << vec.i << "]";
    return stream;
}
