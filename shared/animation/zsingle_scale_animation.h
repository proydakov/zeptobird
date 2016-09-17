#pragma once

#include <animation/ianimation.h>

class zsingle_scale_animation : public ianimation
{
public:
    zsingle_scale_animation(zfloat max);
    ~zsingle_scale_animation() override;

    void update(ztime ms) override;

    zfloat get_scale()    const override;
    zfloat get_rotation() const override;
    zvec2  get_position() const override;

    void restart();

private:
    const zfloat m_max;
    ztime  m_time;
    zfloat m_scale;
};
