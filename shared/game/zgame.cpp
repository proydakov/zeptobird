#include "zgame.h"

#include <render/irender.h>
#include <scene/zscene.h>

namespace {
const size_t SWAP_SCENE_TIMEOUT{3250};
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
    if(!m_scene->is_done()) {
        m_scene->input();
    }

    if(m_swap_scene_timer > SWAP_SCENE_TIMEOUT) {
        restart();
    }
}

void zgame::update(size_t ms)
{
    m_scene->update(ms);
    if(m_scene->is_done()) {
        m_swap_scene_timer += ms;
    }
}

void zgame::render(irender* render)
{
    render->set_scene_size(m_scene->get_width(), m_scene->get_height());
    m_scene->render(render);
}

void zgame::restart()
{
    m_scene.reset(nullptr);
    m_scene.reset(new zscene());
    m_swap_scene_timer = 0;
}
