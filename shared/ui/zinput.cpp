#include "zinput.h"
#include "zwidget.h"

zinput::zinput(std::vector<std::unique_ptr<zwidget>>& widgets) :
    m_widgets(widgets),
    m_focus(nullptr)
{
}

void zinput::input(touch_event type, int x, int y)
{
    bool process = false;
    zwidget* old_focus = m_focus;
    const zpoint point{x, y};
    for(size_t i = 0; i < m_widgets.size(); i++) {
        auto rect = m_widgets[i]->get_rect();

        if(zpoint_in_rect(rect, point) && m_widgets[i]->input(type)) {
            m_focus = m_widgets[i].get();
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
