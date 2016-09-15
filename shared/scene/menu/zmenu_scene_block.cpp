#include <iostream>

#include <render/irender.h>

#include <model/zmodel.h>
#include <model/zmodel_builder.h>

#include "zmenu_scene_block.h"

zmenu_scene_block::zmenu_scene_block(float width, float height, const zcolor& color, int layer)
{
    //std::cout << "zmenu_scene_block" << std::endl;

    m_position.set_zero();
    m_speed.set_zero();

    std::vector<zvec2> geometry;
    zmodel_builder::generate_rect_model(width, height, geometry);

    std::vector<zvec2> aabb;
    zmodel_builder::generate_rect_aabb(width, height, aabb);

    m_model.reset(new zmodel(geometry, aabb, color, layer));
}

zmenu_scene_block::~zmenu_scene_block()
{
    //std::cout << "~zmenu_scene_block" << std::endl;
}

void zmenu_scene_block::update(size_t ms)
{
    m_position += ms / 1000.0 * m_speed;
}

void zmenu_scene_block::render(irender* render) const
{
    render->render(m_model.get(), get_position(), m_model->get_rotation(), m_model->get_scale());
}

const zvec2& zmenu_scene_block::get_position() const
{
    return m_position;
}

void zmenu_scene_block::set_position(const zvec2& position)
{
    m_position = position;
}

const zvec2& zmenu_scene_block::get_speed() const
{
    return m_speed;
}

void zmenu_scene_block::set_speed(const zvec2& speed)
{
    m_speed = speed;
}
