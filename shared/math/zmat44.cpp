#include <cmath>

#include "zmat44.h"

zmat44::zmat44()
{
}

zmat44::zmat44(const zvec4& c1, const zvec4& c2, const zvec4& c3, const zvec4& c4)
{
    ex = c1;
    ey = c2;
    ez = c3;
    ei = c4;
}

void zmat44::set_zero()
{
    ex.set_zero();
    ey.set_zero();
    ez.set_zero();
    ei.set_zero();
}

void zmat44::set_identity()
{
    ex.x = 1.0f; ey.x = 0.0f; ez.x = 0.0f; ei.x = 0.0f;
    ex.y = 0.0f; ey.y = 1.0f; ez.y = 0.0f; ei.y = 0.0f;
    ex.z = 0.0f; ey.z = 0.0f; ez.z = 1.0f; ei.z = 0.0f;
    ex.i = 0.0f; ey.i = 0.0f; ez.i = 0.0f; ei.i = 1.0f;
}

zvec4 zmul(const zmat44& A, const zvec4& v)
{
    return v.x * A.ex + v.y * A.ey + v.z * A.ez + v.i * A.ei;
}

zmat44 zmul(const zmat44& A, const zmat44& B)
{
    return zmat44(zmul(A, B.ex), zmul(A, B.ey), zmul(A, B.ez), zmul(A, B.ei));
}

zmat44 ztranslate4(const zvec3& position)
{
    zmat44 mtranslate;
    mtranslate.ex.x = 1.0f; mtranslate.ey.x = 0.0f; mtranslate.ez.x = 0.0f; mtranslate.ei.x = position.x;
    mtranslate.ex.y = 0.0f; mtranslate.ey.y = 1.0f; mtranslate.ez.y = 0.0f; mtranslate.ei.y = position.y;
    mtranslate.ex.z = 0.0f; mtranslate.ey.z = 0.0f; mtranslate.ez.z = 1.0f; mtranslate.ei.z = position.z;
    mtranslate.ex.i = 0.0f; mtranslate.ey.i = 0.0f; mtranslate.ez.i = 0.0f; mtranslate.ei.i = 1.0f;
    return mtranslate;
}

zmat44 zrotate4(zfloat rotation)
{
    zmat44 mrotate;
    mrotate.ex.x = +std::cos(rotation); mrotate.ey.x = -std::sin(rotation); mrotate.ez.x = 0.0f; mrotate.ei.x = 0.0f;
    mrotate.ex.y = +std::sin(rotation); mrotate.ey.y = +std::cos(rotation); mrotate.ez.y = 0.0f; mrotate.ei.y = 0.0f;
    mrotate.ex.z = +0.0f;               mrotate.ey.z = +0.0f;               mrotate.ez.z = 1.0f; mrotate.ei.z = 0.0f;
    mrotate.ex.i = +0.0f;               mrotate.ey.i = +0.0f;               mrotate.ez.i = 0.0f; mrotate.ei.i = 1.0f;
    return mrotate;
}

zmat44 zscale4(zfloat scalex, zfloat scaley, zfloat scalez)
{
    zmat44 mscale;
    mscale.ex.x = scalex; mscale.ey.x = 0.0f;   mscale.ez.x = 0.0f;   mscale.ei.x = 0.0f;
    mscale.ex.y = 0.0f;   mscale.ey.y = scaley; mscale.ez.y = 0.0f;   mscale.ei.y = 0.0f;
    mscale.ex.z = 0.0f;   mscale.ey.z = 0.0f;   mscale.ez.z = scalez; mscale.ei.z = 0.0f;
    mscale.ex.i = 0.0f;   mscale.ey.i = 0.0f;   mscale.ez.i = 0.0f;   mscale.ei.i = 1.0f;
    return mscale;
}

zmat44 zortho(zfloat left, zfloat right, zfloat bottom, zfloat top, zfloat near, zfloat far)
{
    zmat44 matrix_impl;
    zfloat* matrix = (zfloat*)(&matrix_impl);

    zfloat r_l = right - left;
    zfloat t_b = top - bottom;
    zfloat f_n = far - near;
    zfloat tx = - (right + left) / (right - left);
    zfloat ty = - (top + bottom) / (top - bottom);
    zfloat tz = - (far + near) / (far - near);

    matrix[0] = 2.0f / r_l;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = tx;

    matrix[4] = 0.0f;
    matrix[5] = 2.0f / t_b;
    matrix[6] = 0.0f;
    matrix[7] = ty;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 2.0f / f_n;
    matrix[11] = tz;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;

    return matrix_impl;
}
