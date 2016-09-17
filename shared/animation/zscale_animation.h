#pragma once

#include <animation/ianimation.h>

class zscale_animation : public ianimation
{
public:
    zscale_animation(zfloat max);
    ~zscale_animation() override;

    void update(ztime ms) override;

    zfloat get_scale()    const override;
    zfloat get_rotation() const override;
    zvec2  get_position() const override;

private:
    const zfloat m_max;
    ztime  m_time;
    zfloat m_scale;
};
