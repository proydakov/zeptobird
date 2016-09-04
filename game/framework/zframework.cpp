#include <chrono>
#include <iostream>

#include "zframework.h"

#include <render/impl/zgles2_render.h>
#include <scene/zscene.h>

zframework::zframework(const iresource* resource) :
    m_resource(resource),
    m_render(new zgles2_render(resource)),
    m_scene(new zscene()),
    m_time(0)
{
    std::cout << "resource: " << resource << std::endl;
}

zframework::~zframework()
{
}

void zframework::init(int width, int height)
{
    m_render->init(width, height);
}

void zframework::deinit()
{
    m_render->deinit();
}

void zframework::input()
{
    m_scene->input();
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
    m_scene->update(delta);

    m_time = millis;
    
    if(!m_scene->is_hero_alive()) {
        const zcolor color{187.0 / 255, 10.0 / 255, 30.0 / 255};
        m_render->set_background_color(color);
    }
}

void zframework::render()
{
    /// @todo : using vbo and swap calls
    m_render->render();
    m_scene->render(m_render.get());
}
