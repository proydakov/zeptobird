#include <iostream>

#include <render/irender.h>
#include <model/zmodel.h>
#include <model/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zcircle_body.h>

#include "zscene_coin_object.h"

zscene_coin_object::zscene_coin_object(zworld* world, float radius, int layer)
{
    std::cout << "zscene_coin_object" << std::endl;

    m_body.reset(new zcircle_body(radius));
    world->add_body(m_body.get());

    std::vector<zvec2> geometry;
    zmodel_builder::generate_circle_model(radius, 30, geometry);

    std::vector<zvec2> aabb;
    zmodel_builder::generate_circle_aabb(radius, aabb);

    const zcolor color{255.0 / 255, 255.0 / 255, 0.0 / 255};

    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zscene_coin_object::~zscene_coin_object()
{
    std::cout << "~zscene_coin_object" << std::endl;
}

void zscene_coin_object::update(size_t ms)
{
}

void zscene_coin_object::render(irender* render) const
{
    if(m_body->get_active()) {
        render->render(m_model.get(), get_position(), 1);
    }
}

const zvec2& zscene_coin_object::get_position() const
{
    return m_body->get_position();
}

void zscene_coin_object::set_position(const zvec2& position)
{
    m_body->set_position(position);
}

const zvec2& zscene_coin_object::get_speed() const
{
    return m_body->get_speed();
}

void zscene_coin_object::set_speed(const zvec2& speed)
{
    m_body->set_speed(speed);
}

void zscene_coin_object::set_active(bool active)
{
    m_body->set_active(active);
}
