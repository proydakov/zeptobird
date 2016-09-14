#include "zgame.h"

#include <render/irender.h>
#include <scene/menu/zmenu_scene.h>
#include <scene/game/zgame_scene.h>

zgame::zgame(isound* sound) :
    m_sound(sound),
    m_scene_counter(false)
{
    next();
}

zgame::~zgame()
{
}

void zgame::input()
{
    if(!m_scene->is_done()) {
        m_scene->input();
    }
}

void zgame::update(ztime ms)
{
    m_scene->update(ms);
    if(m_scene->is_done()) {
        next();
    }
}

void zgame::render(irender* render)
{
    render->set_scene_size(m_scene->get_size());
    m_scene->render(render);
}

void zgame::next()
{
    m_scene.reset(nullptr);
    if(m_scene_counter) {
        m_scene.reset(new zgame_scene(m_sound));
    }
    else {
        m_scene.reset(new zmenu_scene(m_sound));
    }
    m_scene_counter = !m_scene_counter;
}
