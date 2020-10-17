#pragma once

#include <memory>
#include <common/ztime.h>
#include <common/zsize.h>
#include <common/zinput.h>

#include <platform/zplatform.h>

class iscene;
class irender;

class zrecord;
class zplatform;

class zgame final
{
public:
    zgame(zplatform& platform);
    ~zgame();

    void input(touch_event, int x, int y);
    void update(ztime);
    void render(irender*);

private:
    void next();

private:
    zplatform m_platform;

    std::unique_ptr<zrecord> m_record;
    std::unique_ptr<iscene> m_scene;
    zsize m_scene_size;

    bool m_scene_counter;
    bool m_scene_resized;
};
