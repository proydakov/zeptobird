#pragma once

#include <phys/ibody.h>

class zrect_body : public ibody
{
public:
    zrect_body(zfloat width, zfloat height);
    ~zrect_body() override;

    zbody_def::btype get_type() const override;
    zaabb get_aabb() const override;

    zfloat get_width() const;
    zfloat get_height() const;

private:
    zfloat m_width;
    zfloat m_height;
};
