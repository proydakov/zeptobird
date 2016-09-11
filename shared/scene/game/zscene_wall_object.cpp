#include <iostream>

#include <render/irender.h>
#include <model/zmodel.h>
#include <model/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zrect_body.h>

#include "zscene_wall_object.h"

zscene_wall_object::zscene_wall_object(zworld* world, float width, float height)
{
    std::cout << "zscene_wall_object" << std::endl;

    m_body.reset(new zrect_body(width, height));
    world->add_body(m_body.get());

    std::vector<zvec2> geometry;
    zmodel_builder::generate_rect_model(width, height, geometry);

    std::vector<zvec2> aabb;
    zmodel_builder::generate_rect_aabb(width, height, aabb);

    const zcolor color{0.0 / 255, 0.0 / 255, 0.0 / 255};
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
    render->render(m_model.get(), get_position(), 1);
}

const zvec2& zscene_wall_object::get_position() const
{
    return m_body->get_position();
}

void zscene_wall_object::set_position(const zvec2& position)
{
    m_body->set_position(position);
}

const zvec2& zscene_wall_object::get_speed() const
{
    return m_body->get_speed();
}

void zscene_wall_object::set_speed(const zvec2& speed)
{
    m_body->set_speed(speed);
}

void zscene_wall_object::set_size(zfloat width, zfloat height)
{
    m_body->set_size(width, height);
    zmodel_builder::generate_rect_model(width, height, m_model->get_geom_ref());
    zmodel_builder::generate_rect_aabb(width, height, m_model->get_aabb_ref());
}
