#pragma once

#include <memory>

#include <math/zmath.h>
#include <common/ztime.h>
#include <common/zrect.h>
#include <common/zinput.h>
#include <render/irenderable.h>

class irender;
class ianimation;

class zwidget : public irenderable
{
public:
    zwidget(int layer);
    zwidget(int layer, std::unique_ptr<ianimation>&& animator);
    ~zwidget() override;

    void update(ztime ms);
    void render(irender& render) const;

    zrect get_rect() const;

    virtual bool input(touch_event type) = 0;

    const zvec2& get_position() const;
    void set_position(const zvec2& position);

    zfloat get_rotation() const;
    void set_rotation(zfloat rotation);

    zfloat get_scale() const;
    void set_scale(zfloat scale);

    void set_visible(bool state);
    bool get_visible() const;

    int get_layer() const override;

    const std::vector<zvec2>& get_aabb_geom() const override;
    const std::vector<zvec2>& get_colored_geom() const override;
    const zcolor& get_color() const override;

    const std::vector<zvec2>& get_textured_geom() const override;
    const std::vector<zvec2>& get_textured_coord() const override;
    const std::string& get_texture_name() const override;

protected:
    void set_color(const zcolor& color);

    std::vector<zvec2>& get_geom_ref();
    std::vector<zvec2>& get_aabb_ref();

    std::vector<zvec2>& get_textured_geom_ref();
    std::vector<zvec2>& get_textured_coord_ref();

private:
    virtual zrect get_rect_impl() const = 0;

private:
    std::unique_ptr<ianimation> m_animator;
    bool m_visible;

    std::vector<zvec2> m_geom;
    std::vector<zvec2> m_aabb;

    std::vector<zvec2> m_textured_geom;
    std::vector<zvec2> m_textured_coord;

    const int m_layer;
    zcolor    m_color;

    zvec2  m_position;
    zfloat m_rotation;
    zfloat m_scale;

    static const std::string m_texture_name;
};
