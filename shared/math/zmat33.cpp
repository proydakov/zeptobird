#include <cmath>

#include "zmat33.h"

zmat33::zmat33()
{
}

zmat33::zmat33(const zvec3& c1, const zvec3& c2, const zvec3& c3)
{
    ex = c1;
    ey = c2;
    ez = c3;
}

void zmat33::set_zero()
{
    ex.set_zero();
    ey.set_zero();
    ez.set_zero();
}

void zmat33::set_identity()
{
    ex.x = 1.0f; ey.x = 0.0f; ez.x = 0.0f;
    ex.y = 0.0f; ey.y = 1.0f; ez.y = 0.0f;
    ex.z = 0.0f; ey.z = 0.0f; ez.z = 1.0f;
}

zvec3 zmul(const zmat33& A, const zvec3& v)
{
    return v.x * A.ex + v.y * A.ey + v.z * A.ez;
}

zmat33 zmul(const zmat33& A, const zmat33& B)
{
    return zmat33(zmul(A, B.ex), zmul(A, B.ey), zmul(A, B.ez));
}

zmat33 ztranslate3(const zvec2& position)
{
    zmat33 mtranslate;
    mtranslate.ex.x = 1.0f; mtranslate.ey.x = 0.0f; mtranslate.ez.x = position.x;
    mtranslate.ex.y = 0.0f; mtranslate.ey.y = 1.0f; mtranslate.ez.y = position.y;
    mtranslate.ex.z = 0.0f; mtranslate.ey.z = 0.0f; mtranslate.ez.z = 1.0f;
    return mtranslate;
}

zmat33 zrotate3(zfloat rotation)
{
    zmat33 mrotate;
    mrotate.ex.x = +std::cos(rotation); mrotate.ey.x = -std::sin(rotation); mrotate.ez.x = 0.0f;
    mrotate.ex.y = +std::sin(rotation); mrotate.ey.y = +std::cos(rotation); mrotate.ez.y = 0.0f;
    mrotate.ex.z = +0.0f;               mrotate.ey.z = +0.0f;               mrotate.ez.z = 1.0f;
    return mrotate;
}

zmat33 zscale3(zfloat scalex, zfloat scaley)
{
    zmat33 mscale;
    mscale.ex.x = scalex; mscale.ey.x = 0.0f;   mscale.ez.x = 0.0f;
    mscale.ex.y = 0.0f;   mscale.ey.y = scaley; mscale.ez.y = 0.0f;
    mscale.ex.z = 0.0f;   mscale.ey.z = 0.0f;   mscale.ez.z = 1.0f;
    return mscale;
}
