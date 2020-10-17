#pragma once

#include <functional>

#include <math/zmath.h>
#include <common/zsize.h>
#include <render/zcolor.h>

class irenderable;

class irender
{
public:
    using resize_callback_t = std::function<void(const zsize&)>;

    virtual ~irender();

    virtual void resize(const zsize& view_size) = 0;

    virtual void render(const irenderable&, const zvec2& pos, zfloat rot, zfloat scale) = 0;
    virtual void render() = 0;

    virtual void set_scene_size(const zsize& scene_size) = 0;
    virtual void set_background_color(const zcolor& color) = 0;
    virtual void set_aabb_color(const zcolor& color) = 0;
    virtual void set_aabb_visible(bool visible) = 0;

    virtual zvec2 view_2_scene(const zvec2& view) = 0;

    virtual void set_scene_size_change_callback(const resize_callback_t&) = 0;
    virtual size_t get_vertex_statistic() const = 0;
};
