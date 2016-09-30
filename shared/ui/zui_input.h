#pragma once

#include <vector>
#include <memory>

#include <common/zinput.h>

class zwidget;

class zui_input
{
public:
    zui_input();

    void input(touch_event type, int x, int y);

    void add_widget(zwidget* widget);

private:
    std::vector<zwidget*> m_widgets;
    zwidget* m_focus;
};
