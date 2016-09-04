#include <cmath>

#include "zmodel_builder.h"

void zmodel_builder::generate_circle(float radius, int angle, std::vector<zvec2>& buffer)
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