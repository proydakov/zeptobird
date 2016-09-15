#include "zrect.h"

zrect::zrect(const zpoint& center, int width, int height) :
    min{center.x - width / 2, center.y - height / 2 },
    max{center.x + width / 2, center.y + height / 2 }
{
}

bool zpoint_in_rect(const zrect& rect, const zpoint& point)
{
    bool c1 = point > rect.min;
    bool c2 = point < rect.max;
    return c1 && c2;
}

std::ostream& operator<< (std::ostream& stream, const zrect& rect)
{
    stream << "{" << rect.min << ", " << rect.max << "}";
    return stream;
}
