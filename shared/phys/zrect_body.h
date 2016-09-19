#pragma once

#include <phys/ibody.h>

class zrect_body : public ibody
{
public:
    zrect_body(zfloat width, zfloat height);
    ~zrect_body() override;

    zaabb get_aabb() const override;

    void set_size(zfloat width, zfloat height);

    zfloat get_width() const;
    zfloat get_height() const;

private:
    zfloat m_width;
    zfloat m_height;
};
