#pragma once

class irender;
class zscene;

#include <memory>

class zgame final
{
public:
    zgame();
    ~zgame();

    void input();
    void update(size_t ms);
    void render(irender* render);

private:
    void restart();

private:
    std::unique_ptr<zscene> m_scene;
    size_t m_swap_scene_timer;
};
