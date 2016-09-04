#pragma once

#include <phys/ibody.h>

class zcircle_body : public ibody
{
public:
    zcircle_body(zfloat radius);
    ~zcircle_body() override;

    virtual zbody_def::btype get_type() const override;

    zfloat get_radius() const;

private:
    zfloat m_radius;
};
