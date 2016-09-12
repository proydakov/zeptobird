#pragma once

#include <common/ztypes.h>

struct color_vertex
{
    zfloat position[3];
    zfloat color   [3];
};

struct texture_vertex
{
    zfloat position[3];
    zfloat texture [2];
};
