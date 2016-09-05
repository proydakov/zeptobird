#include <chrono>
#include <iostream>

#include "zframework.h"

#include <render/impl/zgles2_render.h>
#include <game/zgame.h>

zframework::zframework(const iresource* resource) :
    m_resource(resource),
    m_render(new zgles2_render(resource)),
    m_game(new zgame()),
    m_time(0)
{
}

zframework::~zframework()
{
    deinit();
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
    m_game->update(delta);

    m_time = millis;
}

void zframework::render()
{
    /// @todo : using vbo and swap calls
    m_render->render();
    m_game->render(m_render.get());
}
