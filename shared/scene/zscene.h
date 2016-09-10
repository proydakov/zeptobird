#pragma once

#include <memory>
#include <vector>
#include <random>

#include <render/zcolor.h>

class irender;
class zworld;
class iscene_object;
class zscene_hero_object;
class zscene_wall_object;
class zscene_coin_object;

class zscene
{
public:
    zscene();
    ~zscene();

    void input();
    void update(size_t ms);
    void render(irender* render) const;

    int get_width() const;
    int get_height() const;

    bool is_done() const;

private:
    void update_blocks();
    void update_coins();
    void update_hero();

private:
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
    bool   m_done;
};
