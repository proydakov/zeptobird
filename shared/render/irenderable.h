#pragma once

#include <vector>
#include <math/zmath.h>
#include <render/zcolor.h>

class irenderable
{
public:
    virtual ~irenderable();

    virtual int get_layer() const = 0;

    virtual const std::vector<zvec2>& get_aabb() const = 0;
    virtual const std::vector<zvec2>& get_geom() const = 0;
    virtual const zcolor& get_color() const = 0;

    virtual const std::vector<zvec2>& get_textured_geom() const = 0;
    virtual const std::vector<zvec2>& get_textured_coord() const = 0;
    virtual const std::string& get_texture_name() const = 0;
};
