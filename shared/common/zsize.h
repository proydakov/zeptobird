#pragma once

struct zsize
{
    int width;
    int height;
};

bool operator==(const zsize& left, const zsize& right);
bool operator!=(const zsize& left, const zsize& right);
