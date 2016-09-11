#pragma once

class isound;
class irender;

class iscene;

#include <memory>

class zgame final
{
public:
    zgame(isound* sound);
    ~zgame();

    void input();
    void update(size_t ms);
    void render(irender* render);

private:
    void next();

private:
    isound* m_sound;
    bool m_scene_counter;
    std::unique_ptr<iscene> m_scene;
};
