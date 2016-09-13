#include <cmath>

#include "zfps_calculator.h"

namespace {
    size_t CYCLE_TIMEOUT = 250;
}

zfps_calculator::zfps_calculator() :
    m_frame_counter(0),
    m_delta_time(0),
    m_fps(0)
{
}

void zfps_calculator::update(size_t ms)
{
    m_delta_time += ms;
    m_frame_counter++;
    if(m_delta_time > CYCLE_TIMEOUT) {
        m_fps = 1.0 * m_frame_counter / m_delta_time * 1000;
        m_fps = std::roundf(m_fps * 100) / 100;
        m_frame_counter = 0;
        m_delta_time -= CYCLE_TIMEOUT;
    }
}

float zfps_calculator::get_fps()
{
    return m_fps;
}
