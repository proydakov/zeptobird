#include <chrono>
#include <iostream>

#include <game/zgame.h>
#include <common/ztime.h>
#include <common/zprofiler.h>
#include <render/impl/zgles2_render.h>

#include "zframework.h"
#include "impl/zdebug.h"
#include "impl/znodebug.h"

namespace {

const bool DEBUG_ENGINE = true;

}

zframework::zframework(const zplatform& platform) :
    m_platform(platform),
    m_render(new zgles2_render(m_platform.get_resource())),
    m_game(new zgame(m_platform.get_sound())),
    m_time(0)
{
    if(DEBUG_ENGINE) {
        m_debug.reset(new zdebug(m_render.get()));
    }
    else {
        m_debug.reset(new znodebug());
    }
}

zframework::~zframework()
{
    deinit();

    std::cout << "~zframework" << std::endl;
}

void zframework::init(int width, int height)
{
    const zsize size{width, height};
    m_render->init(size);
}

void zframework::deinit()
{
    m_render->deinit();
}

void zframework::input(touch_event type, int x, int y)
{
    auto scene = m_render->view_2_scene(zvec2(x, y));
    /// view Y down, scene Y up
    scene.y *= -1;
    m_game->input(type, scene.x, scene.y);
}

void zframework::update()
{
    zprofiler prof("update", 1);
    
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = static_cast<ztime>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());

    if(0 == m_time) {
        m_time = millis;
    }

    const ztime delta = static_cast<ztime>(millis - m_time);

    m_game->update(delta);
    m_debug->update(delta);

    m_time = millis;
}

void zframework::render()
{
    zprofiler prof("render", 20);

    m_render->prepare();
    m_game->render(m_render.get());
    m_debug->render(m_render.get());
    m_render->render();
}

void zframework::pause()
{
    m_time = 0;
}
