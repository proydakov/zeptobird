#include "zvec4.h"

zvec4::zvec4()
{
}

zvec4::zvec4(zfloat x_, zfloat y_, zfloat z_, zfloat w_) : x(x_), y(y_), z(z_), w(w_)
{
}

void zvec4::set_zero()
{
    x = 0.0f; y = 0.0f; z = 0.0f;
}

void zvec4::set(zfloat x_, zfloat y_, zfloat z_, zfloat w_)
{
    x = x_; y = y_; z = z_; w = w_;
}

zvec4 zvec4::operator -() const
{
    zvec4 v;
    v.set(-x, -y, -z, -w);
    return v;
}

void zvec4::operator += (const zvec4& v)
{
    x += v.x; y += v.y; z += v.z; w += v.w;
}

void zvec4::operator -= (const zvec4& v)
{
    x -= v.x; y -= v.y; z -= v.z; w -= v.w;
}

void zvec4::operator *= (zfloat s)
{
    x *= s; y *= s; z *= s; w *= s;
}

void zvec4::operator /= (zfloat a)
{
    x /= a; y /= a; z /= a; w /= a;
}

zvec4 operator * (zfloat s, const zvec4& a)
{
    return zvec4(s * a.x, s * a.y, s * a.z, s * a.w);
}

zvec4 operator + (const zvec4& a, const zvec4& b)
{
    return zvec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

zvec4 operator - (const zvec4& a, const zvec4& b)
{
    return zvec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

std::ostream& operator<< (std::ostream& stream, const zvec4& vec)
{
    stream << "[" << vec.x << ", " << vec.y  << ", " << vec.z << ", " << vec.w << "]";
    return stream;
}
