#include <cmath>
#include <cassert>
#include <algorithm>

#include "zworld.h"

#include "zrect_body.h"
#include "zcircle_body.h"

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

void zworld::update(size_t ms)
{
    if(!m_hero) {
        return;
    }
    m_hero->get_position() += ( 1.0 * ms / 1000 ) * m_gravity;

    for(size_t i = 0; i < m_bodys.size(); i++) {
        if(check_collided(m_hero, m_bodys[i])) {
            m_hero->set_collided(true);
            break;
        }
    }
    //m_hero->set_collided(false);
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
    const zcircle_body* zcircle = static_cast<const zcircle_body*>(b1);
    const zrect_body*   zrect   = static_cast<const zrect_body*>(b2);

    const zvec2 circel_position = b1->get_position();
    const zvec2 rect_position   = b2->get_position();

    const float delta_x = circel_position.x - std::max(rect_position.x, std::min(circel_position.x, rect_position.x + zrect->get_width()));
    const float delta_y = circel_position.y - std::max(rect_position.y, std::min(circel_position.y, rect_position.y + zrect->get_height()));
    return (delta_x * delta_x + delta_y * delta_y) < (zcircle->get_radius() * zcircle->get_radius());
}
