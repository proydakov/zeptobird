#pragma once

#include <memory>

class iresource;
class isound;

class irender;
class zgame;

class zframework final
{
public:
    zframework(iresource* resource, isound* sound);
    ~zframework();

    void init(int width, int height, float angle = 0);
    void deinit();

    void input();
    void update();
    void render();

    void pause();

private:
    iresource* m_resource;
    isound*    m_sound;

    std::unique_ptr<irender> m_render;
    std::unique_ptr<zgame>   m_game;

    size_t m_time;
};
