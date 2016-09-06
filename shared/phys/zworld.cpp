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
    zvec2 position = m_hero->get_position();
    position += ( 1.0 * ms / 1000 ) * m_gravity;
    m_hero->set_position(position);

    for(size_t i = 0; i < m_bodys.size(); i++) {
        if(check_collided(m_hero, m_bodys[i])) {
            m_hero->set_collided(true);
            break;
        }
    }
}

bool zworld::check_collided(const ibody* b1, const ibody* b2) const
{
    auto aabb1 = b1->get_aabb();
    auto aabb2 = b2->get_aabb();

    const bool aabb_collided = test_AABB_AABB_SIMD(aabb1, aabb2);
    if(!aabb_collided) {
        return false;
    }

    bool collided = false;
    if(zbody_def::btype::circle == b1->get_type() && zbody_def::btype::rect == b2->get_type()) {
        collided = check_circle_and_rect_collided(b1, b2);
    }
    return collided;
}

bool zworld::check_circle_and_rect_collided(const ibody* b1, const ibody* b2) const
{
    const zcircle_body* zcircle = static_cast<const zcircle_body*>(b1);
    const zrect_body*   zrect   = static_cast<const zrect_body*>(b2);

    const zvec2 circel_center = b1->get_position();
    const zvec2 rect_center   = b2->get_position();

    const zvec2 aabb_half_extents(zrect->get_width() / 2, zrect->get_height() / 2);

    // Get difference vector between both centers
    zvec2 difference = circel_center - rect_center;
    const zvec2 clamped = zclamp(difference, -aabb_half_extents, aabb_half_extents);

    // Add clamped value to AABB_center and we get the value of box closest to circle
    const zvec2 closest = rect_center + clamped;

    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - circel_center;
    return difference.length() < zcircle->get_radius();
}
