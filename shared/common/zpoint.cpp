#include "zpoint.h"

bool operator>=(const zpoint& p1, const zpoint& p2)
{
    return p1.x >= p2.x && p1.y >= p2.y;
}

bool operator<=(const zpoint& p1, const zpoint& p2)
{
    return p1.x <= p2.x && p1.y <= p2.y;
}

std::ostream& operator<< (std::ostream& stream, const zpoint& point)
{
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}
