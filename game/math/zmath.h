#pragma once

#include <ostream>

typedef float zfloat;

struct zvec2
{
    // methods

    zvec2();
    zvec2(zfloat x_, zfloat y_);
    ~zvec2();

    void set_zero();

    void set(zfloat x_, zfloat y_);

    zvec2 operator -() const;

    void operator += (const zvec2& v);

    void operator -= (const zvec2& v);

    void operator *= (zfloat a);

    void operator /= (zfloat a);

    zfloat length() const;

    // data

    zfloat x, y;
};

zvec2 operator * (zfloat s, const zvec2& a);
zvec2 operator + (const zvec2& a, const zvec2& b);

std::ostream& operator<< (std::ostream& stream, const zvec2& vec);
