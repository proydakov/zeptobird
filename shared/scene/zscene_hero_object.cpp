#include <iostream>

#include <render/irender.h>
#include <render/zmodel.h>
#include <render/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zcircle_body.h>

#include "zscene_hero_object.h"

zscene_hero_object::zscene_hero_object(zworld* world)
{
    std::cout << "zscene_hero_object" << std::endl;

    const float radius(10);

    m_body.reset(new zcircle_body(radius));
    world->set_hero(m_body.get());

    std::vector<zvec2> geometry;
    zmodel_builder::generate_circle_model(radius, 10, geometry);

    std::vector<zvec2> aabb;
    zmodel_builder::generate_circle_aabb(radius, aabb);

    const zcolor color{0, 0, 1};
    const int layer{1};

    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zscene_hero_object::~zscene_hero_object()
{
    std::cout << "~zscene_hero_object" << std::endl;
}

void zscene_hero_object::update(size_t ms)
{
}

void zscene_hero_object::render(irender* render) const
{
    render->render(m_model.get(), get_position());
}

const zvec2& zscene_hero_object::get_position() const
{
    return m_body->get_position();
}

void zscene_hero_object::set_position(const zvec2& position)
{
    m_body->set_position(position);
}

bool zscene_hero_object::is_alive() const
{
    return !m_body->get_collided();
}
