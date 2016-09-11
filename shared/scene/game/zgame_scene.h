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

class zgame_scene final : public iscene
{
public:
    zgame_scene(isound* sound);
    ~zgame_scene() override;

    void input() override;
    void update(size_t ms) override;
    void render(irender* render) const override;

    zsize get_size() const override;

    bool is_done() const override;

private:
    void update_blocks();
    void update_coins();
    void update_hero();

private:
    isound* m_sound;

    std::vector<std::unique_ptr<zwidget>> m_widgets;
    ztext_widget* m_score_widget;

    zscene_hero_object*     m_hero;
    std::unique_ptr<zworld> m_world;

    std::vector<std::unique_ptr<iscene_object>> m_objects;
    std::vector<std::pair<zscene_wall_object*, zscene_wall_object*>> m_blocks;
    std::vector<zscene_coin_object*> m_coins;

    zcolor m_background_color;

    std::random_device              m_rd;
    std::mt19937                    m_gen;
    std::uniform_int_distribution<> m_dis;

    size_t m_score;
    bool   m_game_over;
    size_t m_game_over_timer;
};
