#include <cmath>
#include <iostream>

#include "zmath.h"

zvec2::zvec2()
{
    //std::cout << "zvec2" << std::endl;
}

zvec2::zvec2(zfloat x_, zfloat y_) : x(x_), y(y_)
{
    //std::cout << "zvec2 inited" << std::endl;
}

zvec2::~zvec2()
{
    //std::cout << "~zvec2" << std::endl;
}

void zvec2::set_zero()
{
    x = 0.0f;
    y = 0.0f;
}

void zvec2::set(zfloat x_, zfloat y_)
{
    x = x_;
    y = y_;
}

zvec2 zvec2::operator -() const
{
    zvec2 v; v.set(-x, -y);
    return v;
}

void zvec2::operator += (const zvec2& v)
{
    x += v.x; y += v.y;
}

void zvec2::operator -= (const zvec2& v)
{
    x -= v.x; y -= v.y;
}

void zvec2::operator *= (zfloat a)
{
    x *= a; y *= a;
}

void zvec2::operator /= (zfloat a)
{
    x /= a; y /= a;
}

zfloat zvec2::length() const
{
    return std::sqrt(x * x + y * y);
}

zvec2 operator * (zfloat s, const zvec2& a)
{
    return zvec2(s * a.x, s * a.y);
}

zvec2 operator + (const zvec2& a, const zvec2& b)
{
    return zvec2(a.x + b.x, a.y + b.y);
}

zvec2 operator - (const zvec2& a, const zvec2& b)
{
    return zvec2(a.x - b.x, a.y - b.y);
}

zvec2 zmin(const zvec2& a, const zvec2& b)
{
    return zvec2(std::min(a.x, b.x), std::min(a.y, b.y));
}

zvec2 zmax(const zvec2& a, const zvec2& b)
{
    return zvec2(std::max(a.x, b.x), std::max(a.y, b.y));
}

zvec2 zclamp(const zvec2& a, const zvec2& low, const zvec2& high)
{
    return zmax(low, zmin(a, high));
}

std::ostream& operator<< (std::ostream& stream, const zvec2& vec)
{
    stream << "[" << vec.x << ", " << vec.y << "]";
    return stream;
}
