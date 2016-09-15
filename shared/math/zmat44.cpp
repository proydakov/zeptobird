#include <cmath>
#include <iomanip>

#include "zmat44.h"

zmat44::zmat44()
{
}

zmat44::zmat44(const zvec4& c1, const zvec4& c2, const zvec4& c3, const zvec4& c4)
{
    ex = c1;
    ey = c2;
    ez = c3;
    ew = c4;
}

void zmat44::set_zero()
{
    ex.set_zero();
    ey.set_zero();
    ez.set_zero();
    ew.set_zero();
}

void zmat44::set_identity()
{
    ex.x = 1.0f; ey.x = 0.0f; ez.x = 0.0f; ew.x = 0.0f;
    ex.y = 0.0f; ey.y = 1.0f; ez.y = 0.0f; ew.y = 0.0f;
    ex.z = 0.0f; ey.z = 0.0f; ez.z = 1.0f; ew.z = 0.0f;
    ex.w = 0.0f; ey.w = 0.0f; ez.w = 0.0f; ew.w = 1.0f;
}

zvec4 zmul(const zmat44& A, const zvec4& v)
{
    return v.x * A.ex + v.y * A.ey + v.z * A.ez + v.w * A.ew;
}

zmat44 zmul(const zmat44& A, const zmat44& B)
{
    return zmat44(zmul(A, B.ex), zmul(A, B.ey), zmul(A, B.ez), zmul(A, B.ew));
}

zmat44 ztranslate4(const zvec3& position)
{
    zmat44 mtranslate;
    mtranslate.ex.x = 1.0f; mtranslate.ey.x = 0.0f; mtranslate.ez.x = 0.0f; mtranslate.ew.x = position.x;
    mtranslate.ex.y = 0.0f; mtranslate.ey.y = 1.0f; mtranslate.ez.y = 0.0f; mtranslate.ew.y = position.y;
    mtranslate.ex.z = 0.0f; mtranslate.ey.z = 0.0f; mtranslate.ez.z = 1.0f; mtranslate.ew.z = position.z;
    mtranslate.ex.w = 0.0f; mtranslate.ey.w = 0.0f; mtranslate.ez.w = 0.0f; mtranslate.ew.w = 1.0f;
    return mtranslate;
}

zmat44 zrotate_around_z4(zfloat rotation)
{
    zmat44 mrotate;
    mrotate.ex.x = +std::cos(rotation); mrotate.ey.x = -std::sin(rotation); mrotate.ez.x = 0.0f; mrotate.ew.x = 0.0f;
    mrotate.ex.y = +std::sin(rotation); mrotate.ey.y = +std::cos(rotation); mrotate.ez.y = 0.0f; mrotate.ew.y = 0.0f;
    mrotate.ex.z = +0.0f;               mrotate.ey.z = +0.0f;               mrotate.ez.z = 1.0f; mrotate.ew.z = 0.0f;
    mrotate.ex.w = +0.0f;               mrotate.ey.w = +0.0f;               mrotate.ez.w = 0.0f; mrotate.ew.w = 1.0f;
    return mrotate;
}

zmat44 zscale4(zfloat scalex, zfloat scaley, zfloat scalez)
{
    zmat44 mscale;
    mscale.ex.x = scalex; mscale.ey.x = 0.0f;   mscale.ez.x = 0.0f;   mscale.ew.x = 0.0f;
    mscale.ex.y = 0.0f;   mscale.ey.y = scaley; mscale.ez.y = 0.0f;   mscale.ew.y = 0.0f;
    mscale.ex.z = 0.0f;   mscale.ey.z = 0.0f;   mscale.ez.z = scalez; mscale.ew.z = 0.0f;
    mscale.ex.w = 0.0f;   mscale.ey.w = 0.0f;   mscale.ez.w = 0.0f;   mscale.ew.w = 1.0f;
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

bool zinvert4(const zmat44& src, zmat44& dst)
{
    zfloat inv[16], det;

    const float* m = (const float*)(&src);

    inv[0] = m[5]  * m[10] * m[15] -
            m[5]  * m[11] * m[14] -
            m[9]  * m[6]  * m[15] +
            m[9]  * m[7]  * m[14] +
            m[13] * m[6]  * m[11] -
            m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
            m[4]  * m[11] * m[14] +
            m[8]  * m[6]  * m[15] -
            m[8]  * m[7]  * m[14] -
            m[12] * m[6]  * m[11] +
            m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
            m[4]  * m[11] * m[13] -
            m[8]  * m[5] * m[15] +
            m[8]  * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
            m[4]  * m[10] * m[13] +
            m[8]  * m[5] * m[14] -
            m[8]  * m[6] * m[13] -
            m[12] * m[5] * m[10] +
            m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
            m[1]  * m[11] * m[14] +
            m[9]  * m[2] * m[15] -
            m[9]  * m[3] * m[14] -
            m[13] * m[2] * m[11] +
            m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
            m[0]  * m[11] * m[14] -
            m[8]  * m[2] * m[15] +
            m[8]  * m[3] * m[14] +
            m[12] * m[2] * m[11] -
            m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
            m[0]  * m[11] * m[13] +
            m[8]  * m[1] * m[15] -
            m[8]  * m[3] * m[13] -
            m[12] * m[1] * m[11] +
            m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
            m[0]  * m[10] * m[13] -
            m[8]  * m[1] * m[14] +
            m[8]  * m[2] * m[13] +
            m[12] * m[1] * m[10] -
            m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
            m[1]  * m[7] * m[14] -
            m[5]  * m[2] * m[15] +
            m[5]  * m[3] * m[14] +
            m[13] * m[2] * m[7] -
            m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
            m[0]  * m[7] * m[14] +
            m[4]  * m[2] * m[15] -
            m[4]  * m[3] * m[14] -
            m[12] * m[2] * m[7] +
            m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
            m[0]  * m[7] * m[13] -
            m[4]  * m[1] * m[15] +
            m[4]  * m[3] * m[13] +
            m[12] * m[1] * m[7] -
            m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
            m[0]  * m[6] * m[13] +
            m[4]  * m[1] * m[14] -
            m[4]  * m[2] * m[13] -
            m[12] * m[1] * m[6] +
            m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
            m[1] * m[7] * m[10] +
            m[5] * m[2] * m[11] -
            m[5] * m[3] * m[10] -
            m[9] * m[2] * m[7] +
            m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
            m[0] * m[7] * m[10] -
            m[4] * m[2] * m[11] +
            m[4] * m[3] * m[10] +
            m[8] * m[2] * m[7] -
            m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
            m[0] * m[7] * m[9] +
            m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] -
            m[8] * m[1] * m[7] +
            m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
            m[0] * m[6] * m[9] -
            m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] +
            m[8] * m[1] * m[6] -
            m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0) {
        return false;
    }
    det = 1.0 / det;

    float* inv_out = (float*)(&dst);

    for (int i = 0; i < 16; i++) {
        inv_out[i] = inv[i] * det;
    }
    return true;
}

zvec2 zunproject(const zmat44& mvp, const zvec4& viewport, const zvec2& point)
{
    zmat44 inv;
    zinvert4(mvp, inv);

    zvec4 vec{point.x, point.y, 0, 1};
    vec.x = (vec.x - viewport.x) / viewport.z;
    vec.y = (vec.y - viewport.y) / viewport.w;

    vec *= 2;
    vec -= zvec4(1, 1, 1, 1);

    vec = zmul(inv, vec);
    vec /= vec.w;

    zvec2 scene{vec.x, vec.y};
    return scene;
}

std::ostream& operator<<(std::ostream& stream, const zmat44& mat)
{
    const int w = 10;
    const int p = 3;

    stream << "[" << std::setw(w) << std::setprecision( p ) << mat.ex.x << ", " << std::setw(w) << std::setprecision( p ) << mat.ey.x  << ", " << std::setw(w) << std::setprecision( p ) << mat.ez.x << ", " << std::setw(w) << std::setprecision( p ) << mat.ew.x << "]\n";
    stream << "[" << std::setw(w) << std::setprecision( p ) << mat.ex.y << ", " << std::setw(w) << std::setprecision( p ) << mat.ey.y  << ", " << std::setw(w) << std::setprecision( p ) << mat.ez.y << ", " << std::setw(w) << std::setprecision( p ) << mat.ew.y << "]\n";
    stream << "[" << std::setw(w) << std::setprecision( p ) << mat.ex.z << ", " << std::setw(w) << std::setprecision( p ) << mat.ey.z  << ", " << std::setw(w) << std::setprecision( p ) << mat.ez.z << ", " << std::setw(w) << std::setprecision( p ) << mat.ew.z << "]\n";
    stream << "[" << std::setw(w) << std::setprecision( p ) << mat.ex.w << ", " << std::setw(w) << std::setprecision( p ) << mat.ey.w  << ", " << std::setw(w) << std::setprecision( p ) << mat.ez.w << ", " << std::setw(w) << std::setprecision( p ) << mat.ew.w << "]\n";

    return stream;
}
