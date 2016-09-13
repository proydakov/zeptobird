#pragma once

#include <cstdio>

class zfps_calculator
{
public:
    zfps_calculator();

    void update(size_t ms);

    float get_fps();

private:
    size_t m_frame_counter;
    size_t m_delta_time;
    float  m_fps;
};
