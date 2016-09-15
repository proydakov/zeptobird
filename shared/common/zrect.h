#pragma once

#include <ostream>

#include <common/zpoint.h>

struct zrect
{
    zrect(const zpoint& center, int width, int height);

    zpoint min;
    zpoint max;
};

bool zpoint_in_rect(const zrect& rect, const zpoint& point);

std::ostream& operator<< (std::ostream& stream, const zrect& rect);
