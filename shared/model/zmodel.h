#pragma once

#include <render/imodel.h>

class zmodel : public imodel
{
public:
    zmodel(const std::vector<zvec2>& geometry,
           const std::vector<zvec2>& aabb,
           const zcolor& color, int layer);

    ~zmodel() override;

    const std::vector<zvec2>& get_geom() const override;
    const std::vector<zvec2>& get_aabb() const override;
    const zcolor& get_color() const override;
    int get_layer() const override;

    std::vector<zvec2>& get_geom_ref();
    std::vector<zvec2>& get_aabb_ref();

private:
    std::vector<zvec2> m_geom;
    std::vector<zvec2> m_aabb;
    const zcolor m_color;
    const int    m_layer;
};
