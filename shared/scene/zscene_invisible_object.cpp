#include <iostream>

#include <render/irender.h>
#include <render/zmodel.h>
#include <render/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zrect_body.h>

#include "zscene_invisible_object.h"

zscene_invisible_object::zscene_invisible_object()
{
    std::cout << "zscene_wall_object" << std::endl;

    m_position.set_zero();

    const float width(95.0);
    const float height(95.0);

    std::vector<zvec2> geometry;

    std::vector<zvec2> aabb;
    zmodel_builder::generate_rect_aabb(width, height, aabb);
    
    const zcolor color{0, 1, 0};
    const int layer{0};
    
    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zscene_invisible_object::~zscene_invisible_object()
{
    std::cout << "~zscene_wall_object" << std::endl;
}

void zscene_invisible_object::update(size_t ms)
{
}

void zscene_invisible_object::render(irender* render) const
{
    render->render(m_model.get(), get_position());
}

const zvec2& zscene_invisible_object::get_position() const
{
    return m_position;
}

void zscene_invisible_object::set_position(const zvec2& position)
{
    m_position = position;
}
