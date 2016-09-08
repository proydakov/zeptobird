#include "zgame.h"

#include <render/irender.h>
#include <scene/zscene.h>

namespace {
const zcolor GRAY_COLOR {0.65, 0.65, 0.65};
const zcolor BOOLD_COLOR{187.0 / 255, 10.0 / 255, 30.0 / 255};

const size_t RESTART_TIMEOUT{5000};
}

zgame::zgame(irender* render)
{
    restart();
    render->set_scene_size(m_scene->get_width(), m_scene->get_height());
}

zgame::~zgame()
{
}

void zgame::input()
{
    if(m_play) {
        m_scene->input();
    }

    if(m_time_counter > RESTART_TIMEOUT) {
        restart();
    }
}

void zgame::update(size_t ms)
{
    m_scene->update(ms);
    if(!m_scene->is_hero_alive()) {
        m_play = false;
        m_time_counter += ms;
        m_background_color = BOOLD_COLOR;
    }
    //else {
    //    m_background_color = GRAY_COLOR;
    //}
}

void zgame::render(irender* render)
{
    render->set_background_color(m_background_color);
    m_scene->render(render);
}

void zgame::restart()
{
    m_scene.reset(nullptr);
    m_scene.reset(new zscene());
    m_play = true;
    m_time_counter = 0;
    m_background_color = GRAY_COLOR;
}
