#include <cmath>

#include "zmodel_builder.h"

void zmodel_builder::generate_circle_model(float radius, int angle, std::vector<zvec2>& buffer)
{
    const int section = 360 / angle;

    std::vector<zvec2> temp(section);
    buffer.resize(0);
    buffer.reserve(section * 3);

    int theta = 0;
    int step  = 360 / section;

    size_t i = 0;
    while(theta < 360) {
        float rad = theta * M_PI / 180;

        float x = radius * std::cos(rad);
        float y = radius * std::sin(rad);

        temp[i].set(x, y);

        theta += step;
        i++;
    }

    const size_t tsize = temp.size();
    for(size_t i = 0; i < tsize; i++) {
        buffer.push_back(temp[i]);
        buffer.push_back(zvec2(0, 0));
        size_t next = (i + 1) % tsize;
        buffer.push_back(temp[next]);
    }
}

void zmodel_builder::generate_rect_model(float width, float height, std::vector<zvec2>& buffer)
{
    buffer.resize(0);
    buffer.reserve(6);

    buffer.push_back( zvec2( -width / 2,  height / 2) );
    buffer.push_back( zvec2( -width / 2, -height / 2) );
    buffer.push_back( zvec2( +width / 2, -height / 2) );

    buffer.push_back( zvec2( -width / 2,  height / 2) );
    buffer.push_back( zvec2( +width / 2,  height / 2) );
    buffer.push_back( zvec2( +width / 2, -height / 2) );
}

void zmodel_builder::generate_circle_aabb(float radius, std::vector<zvec2>& buffer)
{
    const float diam = radius * 2;
    generate_rect_aabb(diam, diam, buffer);
}

void zmodel_builder::generate_rect_aabb(float width, float height, std::vector<zvec2>& buffer)
{
    std::vector<zvec2> aabb {
        zvec2(-width / 2, -height / 2),
        zvec2(+width / 2, -height / 2),

        zvec2(+width / 2, -height / 2),
        zvec2(+width / 2,  height / 2),

        zvec2(+width / 2,  height / 2),
        zvec2(-width / 2,  height / 2),

        zvec2(-width / 2,  height / 2),
        zvec2(-width / 2, -height / 2)
    };
    buffer.swap(aabb);
}
