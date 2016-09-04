#pragma once

#include <vector>

#include <math/zmath.h>
#include <render/zcolor.h>

class imodel
{
public:
    virtual ~imodel();

    virtual const std::vector<zvec2>& get_geometry() const = 0;
    virtual const zcolor& get_color() const = 0;
    virtual int get_layer() const = 0;
};
