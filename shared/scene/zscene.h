#pragma once

#include <vector>
#include <memory>

class irender;
class iscene_object;
class zscene_hero_object;
class zworld;

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

    bool is_hero_alive() const;

private:
    zscene_hero_object*     m_hero;
    std::unique_ptr<zworld> m_world;
    std::vector<std::unique_ptr<iscene_object>> m_objects;
};
