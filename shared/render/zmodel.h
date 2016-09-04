#pragma once

#include <render/imodel.h>

class zmodel : public imodel
{
public:
    zmodel(const std::vector<zvec2>& geometry, const zcolor& color, int layer);
    ~zmodel() override;

    const std::vector<zvec2>& get_geometry() const override;
    const zcolor& get_color() const override;
    int get_layer() const override;

private:
    std::vector<zvec2> m_geometry;
    zcolor m_color;
    int    m_layer;
};
