#pragma once

#include <memory>
#include <common/ztime.h>

class iresource;
class isound;

class irender;
class zgame;
class idebug;

class zframework final
{
public:
    zframework(iresource* resource, isound* sound);
    ~zframework();

    void init(int width, int height);
    void deinit();

    void input();
    void update();
    void render();

    void pause();

private:
    iresource* m_resource;
    isound*    m_sound;

    std::unique_ptr<irender> m_render;
    std::unique_ptr<zgame>  m_game;
    std::unique_ptr<idebug> m_debug;

    ztime m_time;
};
