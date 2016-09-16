#include <iostream>

#include <model/zmodel_builder.h>

#include "zcolor_widget.h"

zcolor_widget::zcolor_widget(const zstyle& style, float width, float height, int layer) :
    zwidget(layer),
    m_style(style),
    m_width(width),
    m_height(height),
    m_call_callback(false)
{
    set_color(m_style.main_color);
    zmodel_builder::generate_rect_model(width, height, get_geom_ref());
    zmodel_builder::generate_rect_aabb(width, height, get_aabb_ref());
}

zcolor_widget::~zcolor_widget()
{
}

bool zcolor_widget::input(touch_event type)
{
    if(!m_call_callback) {
        return false;
    }

    switch (type) {
    case touch_event::began:
    case touch_event::move:
        set_color(m_style.hover_color);
        break;

    case touch_event::end:
        if(m_call_callback) {
            m_callback();
        }
        break;

    case touch_event::cancle:
        set_color(m_style.main_color);
        break;
    }

    return true;
}

void zcolor_widget::update(size_t ms)
{
}

zrect zcolor_widget::get_rect() const
{
    zvec2 position = get_position();
    zrect rect(zpoint{static_cast<int>(position.x), static_cast<int>(position.y)}, m_width, m_height);
    return rect;
}

void zcolor_widget::set_release_callback(const std::function<void()>& callback)
{
    m_callback = callback;
    m_call_callback = true;
}
