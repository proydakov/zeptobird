#pragma once

#include <render/irenderable.h>

class zmodel : public irenderable
{
public:
    zmodel(const std::vector<zvec2>& geometry,
           const std::vector<zvec2>& aabb,
           const zcolor& color, int layer);

    ~zmodel() override;

    int get_layer() const override;

    const std::vector<zvec2>& get_aabb() const override;
    const std::vector<zvec2>& get_geom() const override;
    const zcolor& get_color() const override;

    const std::vector<zvec2>& get_textured_geom() const override;
    const std::vector<zvec2>& get_textured_coord() const override;
    const std::string& get_texture_name() const override;

    zfloat get_rotation() const;
    void set_rotation(zfloat rotation);

    zfloat get_scale() const;
    void set_scale(zfloat scale);

    std::vector<zvec2>& get_geom_ref();
    std::vector<zvec2>& get_aabb_ref();

private:
    std::vector<zvec2> m_aabb;
    std::vector<zvec2> m_geom;

    std::vector<zvec2> m_textured_geom;
    std::vector<zvec2> m_textured_coord;

    const int         m_layer;
    const zcolor      m_color;
    const std::string m_texture_name;

    zfloat m_rotation;
    zfloat m_scale;
};
