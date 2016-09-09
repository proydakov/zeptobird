#pragma once

class imodel;
class iresource;

#include <math/zmath.h>
#include <render/zcolor.h>

class irender
{
public:
    irender(const iresource* resource);
    virtual ~irender();

    virtual void init(int width, int height, float angle) = 0;
    virtual void deinit() = 0;

    virtual void prepare() = 0;
    virtual void render(const imodel* model, const zvec2& position) = 0;
    virtual void render() = 0;

    virtual void set_scene_size(int width, int height) = 0;
    virtual void set_background_color(const zcolor& color) = 0;
    virtual void set_aabb_color(const zcolor& color) = 0;

protected:
    const iresource* get_resource() const;

private:
    const iresource* m_resource;
};
