#include <cassert>
#include <algorithm>

#include "zworld.h"

#include "zcircle_body.h"
#include "zrect_body.h"

zworld::zworld(const zvec2& gravity) :
    m_gravity(gravity),
    m_hero(nullptr)
{
}

ibody* zworld::create_body(const zbody_def& def) const
{
    ibody* ptr = nullptr;

    switch(def.type) {
    case zbody_def::btype::circle:
        ptr = new zcircle_body(def.radius);
        break;

    case zbody_def::btype::rect:
        ptr = new zrect_body(def.width, def.height);
        break;

    default:
        break;
    }

    assert(ptr);

    return ptr;
}

void zworld::add_body(ibody* body)
{
    m_bodys.push_back(body);
}

void zworld::remove_body(ibody* body)
{
    auto it = std::remove(m_bodys.begin(), m_bodys.end(), body);
    m_bodys.erase(it, m_bodys.end());
}

void zworld::set_hero(ibody* hero)
{
    m_hero = hero;
}

void zworld::update(int mstime)
{
    if(!m_hero) {
        return;
    }
    m_hero->get_position() += ( 1.0 * mstime / 1000 ) * m_gravity;

    for(size_t i = 0; i < m_bodys.size(); i++) {
        if(check_collided(m_hero, m_bodys[i])) {
            m_hero->set_collided(true);
            break;
        }
    }
}

bool zworld::check_collided(const ibody* b1, const ibody* b2) const
{
    bool collided = false;
    if(zbody_def::btype::circle == b1->get_type() && zbody_def::btype::rect == b2->get_type()) {
        collided = check_circle_and_rect_collided(b1, b2);
    }
    else if(zbody_def::btype::circle == b2->get_type() && zbody_def::btype::rect == b1->get_type()) {
        collided = check_circle_and_rect_collided(b2, b1);
    }
    return collided;
}

bool zworld::check_circle_and_rect_collided(const ibody* b1, const ibody* b2) const
{
    /// @todo : impl me
    return b2->get_position().y > b1->get_position().y ? true : false;
}
