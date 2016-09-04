#pragma once

#include <vector>
#include <math/zmath.h>

class zmodel_builder
{
public:
    static void generate_circle(float radius, int angle, std::vector<zvec2>& buffer);
};
