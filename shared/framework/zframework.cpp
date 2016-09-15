#include <chrono>
#include <iostream>

#include <game/zgame.h>
#include <common/ztime.h>
#include <render/impl/zgles2_render.h>

#include "zframework.h"
#include "impl/zdebug.h"
#include "impl/znodebug.h"

namespace {

const bool DEBUG = true;

}

zframework::zframework(iresource* resource, isound* sound) :
    m_resource(resource),
    m_sound(sound),
    m_render(new zgles2_render(resource)),
    m_game(new zgame(sound)),
    m_time(0)
{
    if(DEBUG) {
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
    if(touch_event::began == type) {
        m_game->input();
    }
}

void zframework::update()
{
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
    m_render->prepare();
    m_game->render(m_render.get());
    m_debug->render(m_render.get());
    m_render->render();
}

void zframework::pause()
{
    m_time = 0;
}
