#pragma once

#include <math/zmath.h>
#include <render/iwidget.h>

class zwidget : public iwidget
{
public:
    zwidget(int layer);
    ~zwidget() override;

    virtual void update(size_t ms) = 0;

    const zvec2& get_position() const;
    void set_position(const zvec2& position);

    zfloat get_scale() const;
    void set_scale(zfloat scale);

    int get_layer() const override;

    const std::vector<zvec2>& get_geom() const override;
    const std::vector<zvec2>& get_aabb() const override;
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
    std::vector<zvec2> m_geom;
    std::vector<zvec2> m_aabb;

    std::vector<zvec2> m_textured_geom;
    std::vector<zvec2> m_textured_coord;

    const int m_layer;
    zcolor    m_color;

    zvec2  m_position;
    zfloat m_scale;

    static const std::string m_texture_name;
};
