#include <random>
#include <iostream>

#include <render/irender.h>
#include <platform/isound.h>
#include <ui/ztext_widget.h>
#include <ui/zcolor_widget.h>

#include "zmenu_scene.h"
#include "zmenu_scene_block.h"

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

    m_widgets.reserve(16);
    {
        std::unique_ptr<zwidget> background_widget(new zcolor_widget(zcolor{ 0x00 / 255.0, 0x64 / 255.0, 0x00 / 255.0 }, 60, 30, 5));
        background_widget->set_position(zvec2{0, 0});
        m_widgets.push_back(std::move(background_widget));
    }
    {
        std::unique_ptr<zwidget> background_widget(new zcolor_widget(zcolor{ 0x00 / 255.0, 0x00 / 255.0, 0x00 / 255.0 }, 50, 20, 6));
        background_widget->set_position(zvec2{0, 0});
        m_widgets.push_back(std::move(background_widget));
    }
    {
        std::unique_ptr<zwidget> play_widget(new ztext_widget("PLAY", 10, 7));
        play_widget->set_position(zvec2{0, 0});
        m_widgets.push_back(std::move(play_widget));
    }
    {
        std::unique_ptr<zwidget> author_widget(new ztext_widget("(c)E.PROYDAKOV@GMAIL.COM", 5, 5));
        author_widget->set_position(zvec2{0, -45});
        m_widgets.push_back(std::move(author_widget));
    }

    m_objects.reserve(1024);
    {
        std::vector<zvec2> speeds{
            zvec2{+31, 0},
            zvec2{-29, 0},
            zvec2{+15, 0},
            zvec2{-11, 0}
        };

        std::vector<zcolor> colors{
            zcolor{0xFF / 255.0, 0x8C / 255.0, 0x00 / 255.0},
            zcolor{0x00 / 255.0, 0xBF / 255.0, 0xFF / 255.0},
            zcolor{0xDC / 255.0, 0x14 / 255.0, 0x3C / 255.0},
            zcolor{0x99 / 255.0, 0x32 / 255.0, 0xCC / 255.0},
            zcolor{0xAD / 255.0, 0xFF / 255.0, 0x2F / 255.0}
        };

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> position_dis(-SCENE_SIZE, SCENE_SIZE);
        std::uniform_int_distribution<> speed_dis(0, speeds.size() - 1);
        std::uniform_int_distribution<> color_dis(0, colors.size() - 1);

        for(int i = -750; i < 0; i++) {
            zvec2 position( position_dis(gen), position_dis(gen) );
            zvec2 speed( speeds[ speed_dis(gen) ] );
            zcolor color( colors[ color_dis(gen) ] );

            std::unique_ptr<zmenu_scene_block> block(new zmenu_scene_block(20, 10, color, i));
            block->set_position(position);
            block->set_speed(speed);
            m_objects.push_back(std::move(block));

        }
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
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update(ms);
        auto position = m_objects[i]->get_position();
        if(position.x < -SCENE_SIZE) {
            position.x = SCENE_SIZE;
            m_objects[i]->set_position(position);
        }
        else if(position.x > SCENE_SIZE) {
            position.x = -SCENE_SIZE;
            m_objects[i]->set_position(position);
        }
    }
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->update(ms);
    }
}

void zmenu_scene::render(irender* render) const
{
    render->set_background_color(m_background_color);
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->render(render);
    }
    for(size_t i = 0; i < m_widgets.size(); i++) {
        const auto& widget = m_widgets[i];
        render->render(widget.get(), widget->get_position(), widget->get_rotation(), widget->get_scale());
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
