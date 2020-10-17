#include <iostream>

#include <game/zgame.h>
#include <common/ztime.h>
#include <common/zclock.h>
#include <common/zprofiler.h>
#include <render/impl/zgles2_render.h>

#include "zframework.h"
#include "impl/zdebug.h"
#include "impl/znodebug.h"

zframework::options zframework::default_opt()
{
    return { false };
}

zframework::zframework(zplatform& platform, int width, int height, options const& opt) :
    m_platform(platform),
    m_time(0)
{
    std::cout << "zframework()" << std::endl;

    m_render = std::make_unique<zgles2_render>(m_platform.get_resource());
    m_game = std::make_unique<zgame>(platform);

    if(opt.debug_render) {
        m_debug = std::make_unique<zdebug>(*m_render);
    }
    else {
        m_debug = std::make_unique<znodebug>();
    }
    
    const zsize size{width, height};
    m_render->resize(size);
}

zframework::~zframework()
{
    m_game.reset();
    m_render.reset();

    std::cout << "~zframework()" << std::endl;
}

void zframework::resize(int width, int height)
{
    const zsize size{width, height};
    m_render->resize(size);
}

void zframework::input(touch_event type, int x, int y)
{
    auto scene = m_render->view_2_scene(zvec2(x, y));
    scene.y *= -1; /// view Y down, scene Y up
    m_game->input(type, scene.x, scene.y);
}

void zframework::update()
{
    //zprofiler prof("update", 1);
    
    auto millis = get_millis();
    if (0 == m_time)
    {
        m_time = millis;
    }

    const ztime delta = static_cast<ztime>(millis - m_time);

    m_game->update(delta);
    m_debug->update(delta);

    m_time = millis;
}

void zframework::render()
{
    //zprofiler prof("render", 20);

    m_game->render(*m_render);
    m_debug->render(*m_render);
    m_render->render();
}

void zframework::pause()
{
    m_time = 0;
}
