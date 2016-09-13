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
