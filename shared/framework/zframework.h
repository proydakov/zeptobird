#pragma once

#include <memory>
#include <optional>
#include <common/ztime.h>
#include <common/zinput.h>
#include <platform/zplatform.h>

class zgame;
class idebug;
class irender;

class zframework final
{
public:
    struct options
    {
        bool debug_render;
    };

    static options default_opt();

    zframework(zplatform&, int width, int height, options const& opt = default_opt());
    ~zframework();

    void resize(int width, int height);

    void input(touch_event type, int x, int y);
    void update();
    void render();

    void pause();

private:
    zplatform m_platform;

    std::unique_ptr<irender> m_render;
    std::unique_ptr<zgame>   m_game;
    std::unique_ptr<idebug>  m_debug;

    ztime m_time;
};
