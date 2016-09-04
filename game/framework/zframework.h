#pragma once

#include <memory>

class irender;
class iresource;

class zscene;

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

private:
    const iresource*         m_resource;
    std::unique_ptr<irender> m_render;
    std::unique_ptr<zscene>  m_scene;

    size_t m_time;
};
