#pragma once

#include <memory>

class irender;
class iresource;

class zgame;

class zframework final
{
public:
    zframework(const iresource* resource);
    ~zframework();

    void init(int width, int height);
    void deinit();

    void input();
    void update();
    void render();

    void pause();

private:
    const iresource*         m_resource;
    std::unique_ptr<irender> m_render;
    std::unique_ptr<zgame>   m_game;

    size_t m_time;
};
