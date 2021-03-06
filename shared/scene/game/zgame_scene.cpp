#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

#include <game/zrecord.h>

#include <phys/zworld.h>
#include <render/irender.h>
#include <platform/isound.h>

#include <ui/ztext_widget.h>

#include <animation/zsingle_scale_animation.h>

#include "zscene_coin_object.h"
#include "zscene_wall_object.h"
#include "zscene_hero_object.h"
#include <scene/zscene_invisible_object.h>

#include "zgame_scene.h"
#include "zgame_scene_logic.h"

namespace
{
const zcolor SKY_COLOR  {0.65, 0.65, 0.65};
const zcolor BLOOD_COLOR{187.0 / 255,  10.0 / 255,  30.0 / 255};

constexpr int SCENE_SIZE = 100;

const zvec2 GRAVITY_ACCELERATION(0.0, -9.8);

const zvec2 JUMP_SPEED( 0.0,  12.5);
const zvec2 WALL_SPEED(-10.0,  0.0);

constexpr float HERO_RADIUS = 6;
constexpr float COIN_RADIUS = 4;

constexpr float WALL_WIDTH = 10;

constexpr int MIN_HOLE_Y = 20;
constexpr int MAX_HOLE_Y = SCENE_SIZE - MIN_HOLE_Y;

constexpr float HOLE_HEIGHT = 22;

constexpr size_t COIN_SCORE = 50;

const std::string MAIN_THEME_MUSIC = "theme";
const std::string CATCH_COIN_SOUND = "coin";
const std::string GAME_OVER_SOUND  = "game-over";

constexpr int GAME_OVER_TIMEOUT = 7000;

constexpr size_t SCORE_WIDTH = 5;

std::string score_2_text(size_t score, size_t width);
}

zgame_scene::zgame_scene(isound& sound, zrecord& record) :
    m_sound(sound),
    m_record(record),
    m_hero(nullptr),
    m_world(new zworld(GRAVITY_ACCELERATION)),
    m_background_color(SKY_COLOR),
    m_gen(m_rd()),
    m_dis(MIN_HOLE_Y, MAX_HOLE_Y),
    m_score(0),
    m_game_over(false),
    m_game_over_timer(0)
{
    std::cout << "zgame_scene" << std::endl;

    m_widgets.reserve(16);

    init_ui();

    m_objects.reserve(16);

    init_scene();
    init_hero();
    init_walls();
    init_coins();

    m_sound.play_music(MAIN_THEME_MUSIC);
}

zgame_scene::~zgame_scene()
{
    std::cout << "~zgame_scene" << std::endl;
}

void zgame_scene::input(touch_event type, int, int)
{
    if(m_game_over) {
        return;
    }
    if(touch_event::began == type) {
        m_hero->set_speed(JUMP_SPEED);
    }
}

void zgame_scene::update(ztime ms)
{
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->update(ms);
    }

    m_world->update(ms);

    update_blocks();
    update_coins();
    update_hero();

    if(m_game_over) {
        m_game_over_timer += ms;
    }
}

void zgame_scene::render(irender& render) const
{
    render.set_background_color(m_background_color);

    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->render(render);
    }

    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->render(render);
    }
}

zsize zgame_scene::get_size() const
{
    return zsize{SCENE_SIZE, SCENE_SIZE};
}

bool zgame_scene::is_done() const
{
    return m_game_over_timer > GAME_OVER_TIMEOUT;
}

void zgame_scene::init_ui()
{
    auto animator = std::make_unique<zsingle_scale_animation>(1.25);
    m_score_animator = animator.get();
    
    auto play_widget = std::make_unique<ztext_widget>(score_2_text(m_score, SCORE_WIDTH), 5, 7, std::move(animator));
    m_score_widget = play_widget.get();

    play_widget->set_position(zvec2{35, 45});
    m_widgets.push_back(std::move(play_widget));

    auto game_over_widget = std::make_unique<ztext_widget>("GAME OVER", 10, 7);
    m_game_over_widget = game_over_widget.get();

    m_widgets.push_back(std::move(game_over_widget));
    m_game_over_widget->set_visible(false);
}

void zgame_scene::init_scene()
{
    const auto size = get_size();
    auto aabb = std::make_unique<zscene_invisible_object>( size.width - 2, size.height - 2, 0 );
    aabb->set_position(zvec2(0, 0));
    m_objects.push_back(std::move(aabb));
}

void zgame_scene::init_hero()
{
    auto hero = std::make_unique<zscene_hero_object>( *m_world, HERO_RADIUS, 1 );
    m_hero = hero.get();
    hero->set_position(zvec2( -SCENE_SIZE / 2 + SCENE_SIZE * 1 / 3, 0));
    m_objects.push_back(std::move(hero));
}

void zgame_scene::init_walls()
{
    const size_t wall_count = 3;
    int hole_x = SCENE_SIZE / 2;
    const int hole_x_step = 2 * SCENE_SIZE / 3;

    for(size_t i = 0; i < wall_count; i++) {
        const float hole_y = m_dis(m_gen);
        hole_params params = zscene_game_logic::create_hole_params(hole_y, HOLE_HEIGHT, SCENE_SIZE);

        std::pair<zscene_wall_object*, zscene_wall_object*> pair;
        {
            auto wall_ptr = std::make_unique<zscene_wall_object>( *m_world, WALL_WIDTH, params.height1, 0 );
            pair.first = wall_ptr.get();

            wall_ptr->set_position(zvec2(hole_x, params.center1));
            wall_ptr->set_speed(WALL_SPEED);
            m_objects.push_back(std::move(wall_ptr));
        }
        {
            auto wall_ptr = std::make_unique<zscene_wall_object>( *m_world, WALL_WIDTH, params.height2, 0 );
            pair.second = wall_ptr.get();

            wall_ptr->set_position(zvec2(hole_x, params.center2));
            wall_ptr->set_speed(WALL_SPEED);
            m_objects.push_back(std::move(wall_ptr));
        }
        m_blocks.push_back(std::move(pair));

        hole_x += hole_x_step;
    }
}

void zgame_scene::init_coins()
{
    const size_t coin_count = 3;
    int coin_x = SCENE_SIZE / 2 + SCENE_SIZE * 1 / 3;
    const int coin_x_step = 2 * SCENE_SIZE / 3;
    for(size_t i = 0; i < coin_count; i++) {
        const float coin_y = m_dis(m_gen) - SCENE_SIZE / 2;

        auto coin = std::make_unique<zscene_coin_object>( *m_world, COIN_RADIUS, 1 );
        coin->set_position(zvec2(coin_x,coin_y));
        coin->set_speed(WALL_SPEED);

        m_coins.push_back(coin.get());
        m_objects.push_back(std::move(coin));

        coin_x += coin_x_step;
    }
}

void zgame_scene::update_blocks()
{
    for(size_t i = 0; i < m_blocks.size(); i++) {
        zvec2 position = m_blocks[i].first->get_position();
        if(position.x < -SCENE_SIZE) {
            const float hole_y = m_dis(m_gen);
            hole_params params = zscene_game_logic::create_hole_params(hole_y, HOLE_HEIGHT, SCENE_SIZE);

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
}

void zgame_scene::update_coins()
{
    for(size_t i = 0; i < m_coins.size(); i++) {
        zvec2 position = m_coins[i]->get_position();
        if(position.x < -SCENE_SIZE) {
            position.x = SCENE_SIZE;
            position.y = m_dis(m_gen) - SCENE_SIZE / 2;
            m_coins[i]->set_active(true);
            m_coins[i]->set_position(position);
        }
    }
}

void zgame_scene::update_hero()
{
    if(m_game_over) {
        return;
    }

    ibody* collided = m_hero->get_collided();
    bool is_alive = true;
    if(collided) {
        zbody_def::btype type = collided->get_type();
        if(zbody_def::btype::rect == type) {
            is_alive = false;
        }
        else if(zbody_def::btype::circle == type) {
            collided->set_active(false);
            m_score += COIN_SCORE;
            m_score_widget->set_text(score_2_text(m_score, SCORE_WIDTH));
            m_sound.play_sound(CATCH_COIN_SOUND);
            m_score_animator->restart();
        }
        else {
            assert(false);
        }
    }

    const zvec2& position = m_hero->get_position();
    const bool on_scene = position.y < (SCENE_SIZE / 2 - HERO_RADIUS) && position.y > (-SCENE_SIZE / 2 + HERO_RADIUS);
    const bool game_over = !(is_alive && on_scene);

    if(game_over) {
        m_game_over_widget->set_visible(true);
        m_sound.stop_music();
        m_sound.play_sound(GAME_OVER_SOUND);
        m_game_over = true;
        m_background_color = BLOOD_COLOR;
        m_record.process(m_record.get_hero_name(), m_score);
    }
}

namespace
{

std::string score_2_text(size_t score, size_t width)
{
    std::stringstream sstream;
    std::string score_str = std::to_string(score);
    for(size_t i = score_str.size(); i < width; i++) {
        sstream << "0";
    }
    sstream << score_str;
    return sstream.str();
}

}
