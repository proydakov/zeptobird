#pragma once

#include <animation/ianimation.h>

class zempty_animation : public ianimation
{
public:
    zempty_animation();
    ~zempty_animation() override;
    
    void update(ztime ms) override;
    
    zfloat get_scale()    const override;
    zfloat get_rotation() const override;
    zvec2  get_position() const override;
};
