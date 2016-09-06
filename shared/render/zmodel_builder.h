#pragma once

#include <vector>
#include <math/zmath.h>

class zmodel_builder
{
public:
    static void generate_circle_model(float radius, int angle, std::vector<zvec2>& buffer);
    static void generate_rect_model(float width, float height, std::vector<zvec2>& buffer);

    static void generate_circle_aabb(float radius, std::vector<zvec2>& buffer);
    static void generate_rect_aabb(float width, float height, std::vector<zvec2>& buffer);
};
