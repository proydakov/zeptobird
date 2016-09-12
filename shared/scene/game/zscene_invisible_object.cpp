#include <iostream>

#include <render/irender.h>
#include <model/zmodel.h>
#include <model/zmodel_builder.h>

#include <phys/zworld.h>
#include <phys/zrect_body.h>

#include "zscene_invisible_object.h"

zscene_invisible_object::zscene_invisible_object(float width, float height, int layer)
{
    std::cout << "zscene_invisible_object" << std::endl;

    m_position.set_zero();
    m_speed.set_zero();

    std::vector<zvec2> geometry;

    std::vector<zvec2> aabb;
    zmodel_builder::generate_rect_aabb(width, height, aabb);

    const zcolor color{0, 1, 0};

    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zscene_invisible_object::~zscene_invisible_object()
{
    std::cout << "~zscene_invisible_object" << std::endl;
}

void zscene_invisible_object::update(size_t ms)
{
}

void zscene_invisible_object::render(irender* render) const
{
    render->render(m_model.get(), get_position(), m_model->get_rotation(), m_model->get_scale());
}

const zvec2& zscene_invisible_object::get_position() const
{
    return m_position;
}

void zscene_invisible_object::set_position(const zvec2& position)
{
    m_position = position;
}

const zvec2& zscene_invisible_object::get_speed() const
{
    return m_speed;
}

void zscene_invisible_object::set_speed(const zvec2& speed)
{
    m_speed = speed;
}
