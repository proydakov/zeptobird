#pragma once

#include <memory>
#include <common/ztime.h>
#include <common/zinput.h>
#include <platform/zplatform.h>

class zgame;
class idebug;
class irender;

class zframework final
{
public:
    zframework(zplatform& platform);
    ~zframework();

    void init(int width, int height);
    void resize(int width, int height);
    void deinit();

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
