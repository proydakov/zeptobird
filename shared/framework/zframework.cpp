#include <stdio.h>
#include <chrono>
#include <sstream>
#include <iostream>

#include "zframework.h"

#include <render/impl/zgles2_render.h>
#include <render/zfps_calculator.h>

#include <ui/ztext_widget.h>

#include <game/zgame.h>

namespace {
    const float FPS_COUNTER_UNIT  = 5;
    const int   FPS_COUNTER_LAYER = 9;

    std::string build_fps_text(float fps)
    {
        char buffer[10];
        snprintf(buffer, 10, "FPS:%5.2f", fps);
        std::string fps_str( buffer );
        return fps_str;
    }
}

zframework::zframework(iresource* resource, isound* sound) :
    m_resource(resource),
    m_sound(sound),
    m_render(new zgles2_render(resource)),
    m_fps_calculator(new zfps_calculator()),
    m_game(new zgame(sound)),
    m_fps_widget(new ztext_widget(build_fps_text(m_fps_calculator->get_fps()), FPS_COUNTER_UNIT, FPS_COUNTER_LAYER)),
    m_time(0)
{
    std::cout << "zframework" << std::endl;

    ztext_widget* text_widget = m_fps_widget.get();
    std::function<void(const zsize&)> size_change([text_widget](const zsize& size) {
        float x = -1 * size.width / 2;
        float y = size.height / 2 - 5;
        text_widget->set_position(zvec2{x, y});
    });
    m_render->set_scene_size_change_callback(size_change);
}

zframework::~zframework()
{
    deinit();

    std::cout << "~zframework" << std::endl;
}

void zframework::init(int width, int height, float angle)
{
    const zsize size{width, height};
    m_render->init(size, angle);
}

void zframework::deinit()
{
    m_render->deinit();
}

void zframework::input()
{
    m_game->input();
}

void zframework::update()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    if(0 == m_time) {
        m_time = millis;
    }

    const size_t delta = millis - m_time;

    m_fps_calculator->update(delta);
    m_fps_widget->set_text(build_fps_text(m_fps_calculator->get_fps()));

    m_game->update(delta);

    m_time = millis;
}

void zframework::render()
{
    m_render->prepare();
    m_game->render(m_render.get());
    m_render->render(m_fps_widget.get(), m_fps_widget->get_position(), m_fps_widget->get_rotation(), m_fps_widget->get_scale());
    m_render->render();
}

void zframework::pause()
{
    m_time = 0;
}
