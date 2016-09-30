#include "zwidget.h"
#include "zui_input.h"

zui_input::zui_input() :
    m_focus(nullptr)
{
}

void zui_input::input(touch_event type, int x, int y)
{
    bool process = false;
    zwidget* old_focus = m_focus;
    const zpoint point{x, y};
    for(size_t i = 0; i < m_widgets.size(); i++) {
        auto rect = m_widgets[i]->get_rect();

        if(zpoint_in_rect(rect, point) && m_widgets[i]->input(type)) {
            m_focus = m_widgets[i];
            process = true;
            break;
        }
    }
    if(!process) {
        m_focus = nullptr;
    }
    if(old_focus && old_focus != m_focus) {
        old_focus->input(touch_event::cancle);
    }
}

void zui_input::add_widget(zwidget* widget)
{
    m_widgets.push_back(widget);
}
