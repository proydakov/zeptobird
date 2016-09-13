#include "zvec3.h"

zvec3::zvec3()
{
}

zvec3::zvec3(zfloat x_, zfloat y_, zfloat z_) : x(x_), y(y_), z(z_)
{
}

void zvec3::set_zero()
{
    x = 0.0f; y = 0.0f; z = 0.0f;
}

void zvec3::set(zfloat x_, zfloat y_, zfloat z_)
{
    x = x_; y = y_; z = z_;
}

zvec3 zvec3::operator -() const
{
    zvec3 v;
    v.set(-x, -y, -z);
    return v;
}

void zvec3::operator += (const zvec3& v)
{
    x += v.x; y += v.y; z += v.z;
}

void zvec3::operator -= (const zvec3& v)
{
    x -= v.x; y -= v.y; z -= v.z;
}

void zvec3::operator *= (zfloat s)
{
    x *= s; y *= s; z *= s;
}

void zvec3::operator /= (zfloat a)
{
    x /= a; y /= a; z /= a;
}

zvec3 operator * (zfloat s, const zvec3& a)
{
    return zvec3(s * a.x, s * a.y, s * a.z);
}

zvec3 operator + (const zvec3& a, const zvec3& b)
{
    return zvec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

zvec3 operator - (const zvec3& a, const zvec3& b)
{
    return zvec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

std::ostream& operator<< (std::ostream& stream, const zvec3& vec)
{
    stream << "[" << vec.x << ", " << vec.y  << ", " << vec.z << "]";
    return stream;
}
