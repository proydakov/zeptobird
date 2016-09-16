#pragma once

#include <ostream>

struct zpoint
{
    int x;
    int y;
};

bool operator>=(const zpoint& p1, const zpoint& p2);
bool operator<=(const zpoint& p1, const zpoint& p2);

std::ostream& operator<< (std::ostream& stream, const zpoint& point);
