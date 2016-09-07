#include <iostream>

#include <phys/zworld.h>
#include <render/irender.h>

#include "zscene.h"
#include "zscene_wall_object.h"
#include "zscene_hero_object.h"
#include "zscene_invisible_object.h"

namespace {
    const int SCENE_SIZE = 100;

    const zvec2 GRAVITY_SPEED(0.0, -9.8);
    const zvec2 JUMP_SPEED (0.0, 9.8);
    const zvec2 WALL_SPEED(-5.0, 0.0);
}

zscene::zscene() :
    m_hero(nullptr),
    m_world(new zworld(GRAVITY_SPEED))
{
    std::cout << "zscene" << std::endl;

    m_objects.reserve(16);
    {
        std::unique_ptr<iscene_object> aabb( new zscene_invisible_object( SCENE_SIZE - 2, SCENE_SIZE - 2 ) );
        aabb->set_position(zvec2(0, 0));
        m_objects.push_back(std::move(aabb));
    }
    {
        std::unique_ptr<iscene_object> wall( new zscene_wall_object( m_world.get(), 10, (SCENE_SIZE - 2) / 2 ) );
        wall->set_position(zvec2(SCENE_SIZE / 2 * 2 / 3, -25));
        wall->set_speed(zvec2(WALL_SPEED));
        m_objects.push_back(std::move(wall));
    }
    {
        std::unique_ptr<iscene_object> wall( new zscene_wall_object( m_world.get(), 10, (SCENE_SIZE - 2) / 2 ) );
        wall->set_position(zvec2(SCENE_SIZE / 2 * 4 / 3, +25));
        wall->set_speed(zvec2(WALL_SPEED));
        m_objects.push_back(std::move(wall));
    }
    {
        auto hero_ptr = new zscene_hero_object( m_world.get(), 7 );
        std::unique_ptr<iscene_object> hero( hero_ptr );
        hero->set_position(zvec2( -SCENE_SIZE / 2 + SCENE_SIZE * 2 / 5, 0));
        hero->set_speed(GRAVITY_SPEED);
        m_objects.push_back(std::move(hero));
        m_hero = hero_ptr;
    }
}

zscene::~zscene()
{
    std::cout << "~zscene" << std::endl;
}

void zscene::input()
{
    zvec2 speed = m_hero->get_speed();
    speed += 1.25 * JUMP_SPEED;
    speed = zmin(speed, JUMP_SPEED);
    m_hero->set_speed(speed);
}

void zscene::update(size_t ms)
{
    m_world->update(ms);
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update(ms);
        zvec2 position = m_objects[i]->get_position();
        if(position.x < -SCENE_SIZE) {
            position.x = SCENE_SIZE;
            m_objects[i]->set_position(position);
        }
    }
}

void zscene::render(irender* render) const
{
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->render(render);
    }
}

int zscene::get_width() const
{
    return SCENE_SIZE;
}

int zscene::get_height() const
{
    return SCENE_SIZE;
}

bool zscene::is_hero_alive() const
{
    return m_hero->is_alive();
}
