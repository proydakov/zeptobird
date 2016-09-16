#pragma once

#include <vector>
#include <memory>

#include <common/zinput.h>

class zwidget;

class zinput
{
public:
    zinput(std::vector<std::unique_ptr<zwidget>>& widgets);

    void input(touch_event type, int x, int y);

private:
    std::vector<std::unique_ptr<zwidget>>& m_widgets;
    zwidget* m_focus;
};
