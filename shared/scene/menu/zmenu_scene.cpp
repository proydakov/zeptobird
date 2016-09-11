#include <iostream>

#include <render/irender.h>
#include <platform/isound.h>
#include <ui/ztext_widget.h>

#include "zmenu_scene.h"

namespace {
const std::string MENU_THEME_MUSIC = "menu";

const zcolor BACKGROUND_COLOR{0.65, 0.65, 0.65};

const int SCENE_SIZE = 100;
}

zmenu_scene::zmenu_scene(isound* sound) :
    m_sound(sound),
    m_background_color(BACKGROUND_COLOR),
    m_done(false)
{
    std::cout << "zmenu_scene" << std::endl;
    m_widgets.reserve(0);

    {
        auto text_widget_ptr = new ztext_widget("Play", 5);
        std::unique_ptr<zwidget> play_widget(text_widget_ptr);
        m_widgets.push_back(std::move(play_widget));
    }

    m_sound->play_music(MENU_THEME_MUSIC);
}

zmenu_scene::~zmenu_scene()
{
    std::cout << "~zmenu_scene" << std::endl;
}

void zmenu_scene::input()
{
    m_done = true;
}

void zmenu_scene::update(size_t ms)
{
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->update(ms);
    }
}

void zmenu_scene::render(irender* render) const
{
    render->set_background_color(m_background_color);
    for(size_t i = 0; i < m_widgets.size(); i++) {
        const auto& widget = m_widgets[i];
        render->render(widget.get(), widget->get_position(), widget->get_scale());
    }
}

zsize zmenu_scene::get_size() const
{
    zsize size{SCENE_SIZE, SCENE_SIZE};
    return size;
}

bool zmenu_scene::is_done() const
{
    return m_done;
}
