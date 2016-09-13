#include "zmat22.h"

zmat22::zmat22()
{
}

zmat22::zmat22(const zvec2& c1, const zvec2& c2)
{
    ex = c1;
    ey = c2;
}

void zmat22::set_identity()
{
    ex.x = 1.0f; ey.x = 0.0f;
    ex.y = 0.0f; ey.y = 1.0f;
}

void zmat22::set_zero()
{
    ex.x = 0.0f; ey.x = 0.0f;
    ex.y = 0.0f; ey.y = 0.0f;
}

zvec2 zmul(const zmat22& A, const zvec2& v)
{
    return zvec2(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}

zmat22 zmul(const zmat22& A, const zmat22& B)
{
    return zmat22(zmul(A, B.ex), zmul(A, B.ey));
}
