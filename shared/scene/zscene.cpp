#include <iostream>

#include <phys/zworld.h>
#include <render/irender.h>

#include "zscene.h"
#include "zscene_wall_object.h"
#include "zscene_hero_object.h"

zscene::zscene() :
    m_hero(nullptr),
    m_world(new zworld(zvec2(0.0, -9.8 / 50)))
{
    std::cout << "zscene" << std::endl;

    m_objects.reserve(16);
    {
        auto hero_ptr = new zscene_hero_object( m_world.get() );
        std::unique_ptr<iscene_object> hero( hero_ptr );
        hero->set_position(zvec2(0.0, 1.0));
        m_objects.push_back(std::move(hero));
        m_hero = hero_ptr;
    }
    {
        std::unique_ptr<iscene_object> wall( new zscene_wall_object( m_world.get() ) );
        wall->set_position(zvec2(0.0, -0.8));
        m_objects.push_back(std::move(wall));
    }
}

zscene::~zscene()
{
    std::cout << "~zscene" << std::endl;
}

void zscene::input()
{
}

void zscene::update(size_t ms)
{
    m_world->update(ms);
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update(ms);
    }
}

void zscene::render(irender* render) const
{
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->render(render);
    }
}

bool zscene::is_hero_alive() const
{
    return m_hero->is_alive();
}
