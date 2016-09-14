#pragma once

#include <common/ztime.h>

class zfps_calculator
{
public:
    zfps_calculator();

    void update(ztime ms);

    float get_fps();

private:
    size_t m_frame_counter;
    size_t m_delta_time;
    float  m_fps;
};
