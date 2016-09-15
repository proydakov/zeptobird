#include "zsize.h"

bool operator==(const zsize& left, const zsize& right)
{
    return left.width == right.width && left.height == right.height;
}

bool operator!=(const zsize& left, const zsize& right)
{
    return left.width != right.width || left.height != right.height;
}
