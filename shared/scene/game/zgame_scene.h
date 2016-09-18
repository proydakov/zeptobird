#pragma once

#include <memory>
#include <vector>
#include <random>

#include <scene/iscene.h>
#include <render/zcolor.h>

class isound;
class irender;

class zworld;
class iscene_object;
class zscene_hero_object;
class zscene_wall_object;
class zscene_coin_object;

class zwidget;
class ztext_widget;

class zrecord;

class zsingle_scale_animation;

class zgame_scene final : public iscene
{
public:
    zgame_scene(isound* sound, zrecord* record);
    ~zgame_scene() override;

    void input(touch_event type, int x, int y) override;
    void update(ztime ms) override;
    void render(irender* render) const override;

    zsize get_size() const override;

    bool is_done() const override;

private:
    void init_ui();
    void init_scene();
    void init_hero();
    void init_walls();
    void init_coins();

    void update_blocks();
    void update_coins();
    void update_hero();

private:
    isound*  m_sound;
    zrecord* m_record;

    std::vector<std::unique_ptr<zwidget>> m_widgets;
    ztext_widget* m_score_widget;
    zsingle_scale_animation* m_score_animator;
    ztext_widget* m_game_over_widget;

    zscene_hero_object*     m_hero;
    std::unique_ptr<zworld> m_world;

    std::vector<std::unique_ptr<iscene_object>> m_objects;
    std::vector<std::pair<zscene_wall_object*, zscene_wall_object*>> m_blocks;
    std::vector<zscene_coin_object*> m_coins;

    zcolor m_background_color;

    std::random_device              m_rd;
    std::mt19937                    m_gen;
    std::uniform_int_distribution<> m_dis;

    int    m_score;
    bool   m_game_over;
    size_t m_game_over_timer;
};
