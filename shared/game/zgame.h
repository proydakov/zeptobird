#pragma once

class isound;
class irender;

class iscene;

#include <memory>
#include <common/ztime.h>

class zgame final
{
public:
    zgame(isound* sound);
    ~zgame();

    void input();
    void update(ztime ms);
    void render(irender* render);

private:
    void next();

private:
    isound* m_sound;
    bool m_scene_counter;
    std::unique_ptr<iscene> m_scene;
};
