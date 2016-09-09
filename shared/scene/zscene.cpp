#include <iostream>

#include <phys/zworld.h>
#include <render/irender.h>

#include "zscene.h"
#include "zscene_wall_object.h"
#include "zscene_hero_object.h"
#include "zscene_invisible_object.h"

#include "zgame_logic.h"

namespace {
const zcolor SKY_COLOR  {0.65, 0.65, 0.65};
const zcolor BLOOD_COLOR{187.0 / 255,  10.0 / 255,  30.0 / 255};

const int SCENE_SIZE = 100;

const zvec2 GRAVITY_SPEED(0.0, -9.8);
const zvec2 JUMP_SPEED (0.0, 9.8);
const zvec2 WALL_SPEED(-10.0, 0.0);

const float HERO_RADIUS = 6;

const float WALL_WIDTH(10);

const int MIN_HOLE_Y = 20;
const int MAX_HOLE_Y = SCENE_SIZE - MIN_HOLE_Y;

const float HOLE_HEIGHT = 20;
}

zscene::zscene() :
    m_hero(nullptr),
    m_world(new zworld(GRAVITY_SPEED)),
    m_background_color(SKY_COLOR),
    m_gen(m_rd()),
    m_dis(MIN_HOLE_Y, MAX_HOLE_Y),
    m_done(false)
{
    std::cout << "zscene" << std::endl;

    m_objects.reserve(16);
    {
        std::unique_ptr<iscene_object> aabb( new zscene_invisible_object( SCENE_SIZE - 2, SCENE_SIZE - 2 ) );
        aabb->set_position(zvec2(0, 0));
        m_objects.push_back(std::move(aabb));
    }
    {
        auto hero_ptr = new zscene_hero_object( m_world.get(), HERO_RADIUS );
        std::unique_ptr<iscene_object> hero( hero_ptr );
        hero->set_position(zvec2( -SCENE_SIZE / 2 + SCENE_SIZE * 1 / 3, 0));
        hero->set_speed(GRAVITY_SPEED);
        m_objects.push_back(std::move(hero));
        m_hero = hero_ptr;
    }
    {
        const size_t wall_count = 3;
        int hole_x = SCENE_SIZE / 2;
        const int hole_x_step = 2 * SCENE_SIZE / 3;
        for(size_t i = 0; i < wall_count; i++) {
            const float hole_y = m_dis(m_gen);
            hole_params params = zgame_logic::create_hole_params(hole_y, HOLE_HEIGHT, SCENE_SIZE);

            std::pair<zscene_wall_object*, zscene_wall_object*> pair;
            {
                zscene_wall_object* wall_ptr = new zscene_wall_object( m_world.get(), WALL_WIDTH, params.height1 );
                pair.first = wall_ptr;

                std::unique_ptr<iscene_object> wall( wall_ptr );
                wall->set_position(zvec2(hole_x, params.center1));
                wall->set_speed(zvec2(WALL_SPEED));
                m_objects.push_back(std::move(wall));
            }
            {
                zscene_wall_object* wall_ptr = new zscene_wall_object( m_world.get(), WALL_WIDTH, params.height2 );
                pair.second = wall_ptr;

                std::unique_ptr<iscene_object> wall( wall_ptr );
                wall->set_position(zvec2(hole_x, params.center2));
                wall->set_speed(zvec2(WALL_SPEED));
                m_objects.push_back(std::move(wall));
            }
            m_blocks.push_back(std::move(pair));

            hole_x += hole_x_step;
        }
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

    for(size_t i = 0; i < m_blocks.size(); i++) {
        zvec2 position = m_blocks[i].first->get_position();
        if(position.x < -SCENE_SIZE) {
            const float hole_y = m_dis(m_gen);
            hole_params params = zgame_logic::create_hole_params(hole_y, HOLE_HEIGHT, SCENE_SIZE);

            position.x = SCENE_SIZE;
            position.y = params.center1;
            m_blocks[i].first->set_position(position);
            m_blocks[i].first->set_size(WALL_WIDTH, params.height1);

            position.x = SCENE_SIZE;
            position.y = params.center2;
            m_blocks[i].second->set_position(position);
            m_blocks[i].second->set_size(WALL_WIDTH, params.height2);
        }
    }

    const zvec2& position = m_hero->get_position();
    bool is_alive = m_hero->is_alive();
    bool on_scene = position.y < (SCENE_SIZE / 2 - HERO_RADIUS) && position.y > (-SCENE_SIZE / 2 + HERO_RADIUS);
    m_done = !(is_alive && on_scene);
    if(m_done) {
        m_background_color = BLOOD_COLOR;
    }
}

void zscene::render(irender* render) const
{
    render->set_background_color(m_background_color);
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

bool zscene::is_done() const
{
    return m_done;
}
