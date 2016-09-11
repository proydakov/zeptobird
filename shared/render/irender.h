#pragma once

class imodel;
class iwidget;
class iresource;

#include <math/zmath.h>
#include <common/zsize.h>
#include <render/zcolor.h>

class irender
{
public:
    irender(const iresource* resource);
    virtual ~irender();

    virtual void init(const zsize& view_size, float angle) = 0;
    virtual void deinit() = 0;

    virtual void prepare() = 0;
    virtual void render(const imodel* model, const zvec2& position, zfloat scale) = 0;
    virtual void render(const iwidget* widget, const zvec2& position, zfloat scale) = 0;
    virtual void render() = 0;

    virtual void set_scene_size(const zsize& scene_size) = 0;
    virtual void set_background_color(const zcolor& color) = 0;
    virtual void set_aabb_color(const zcolor& color) = 0;

protected:
    const iresource* get_resource() const;

private:
    const iresource* m_resource;
};
