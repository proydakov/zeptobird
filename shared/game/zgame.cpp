#include "zgame.h"

#include <render/irender.h>
#include <scene/zscene.h>

namespace {
    const zcolor gray_color {0.65, 0.65, 0.65};
    const zcolor blood_color{187.0 / 255, 10.0 / 255, 30.0 / 255};

    const size_t max_time_counter{5000};
}

zgame::zgame()
{
    restart();
}

zgame::~zgame()
{
}

void zgame::input()
{
    m_scene->input();

    if(m_time_counter > max_time_counter) {
        restart();
    }
}

void zgame::update(size_t ms)
{
    m_scene->update(ms);
    if(!m_scene->is_hero_alive()) {
        m_background_color = blood_color;
        m_time_counter += ms;
    }
}

void zgame::render(irender* render)
{
    render->set_background_color(m_background_color);
    m_scene->render(render);
}

void zgame::restart()
{
    m_scene.reset(nullptr);
    m_scene.reset(new zscene()),
    m_time_counter = (0),
    m_background_color = gray_color;
}
