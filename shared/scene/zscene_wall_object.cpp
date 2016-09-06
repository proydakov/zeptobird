#include <iostream>

#include <render/irender.h>
#include <render/zmodel.h>
#include <render/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zrect_body.h>

#include "zscene_wall_object.h"

zscene_wall_object::zscene_wall_object(zworld* world)
{
    std::cout << "zscene_wall_object" << std::endl;

    const float width(90.0);
    const float height(10.0);

    m_body.reset(new zrect_body(width, height));
    world->add_body(m_body.get());

    std::vector<zvec2> geometry;
    zmodel_builder::generate_rect_model(width, height, geometry);

    std::vector<zvec2> aabb;
    zmodel_builder::generate_rect_aabb(width, height, aabb);

    const zcolor color{0, 1, 0};
    const int layer{0};

    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zscene_wall_object::~zscene_wall_object()
{
    std::cout << "~zscene_wall_object" << std::endl;
}

void zscene_wall_object::update(size_t ms)
{
}

void zscene_wall_object::render(irender* render) const
{
    render->render(m_model.get(), get_position());
}

const zvec2& zscene_wall_object::get_position() const
{
    return m_body->get_position();
}

void zscene_wall_object::set_position(const zvec2& position)
{
    m_body->set_position(position);
}
