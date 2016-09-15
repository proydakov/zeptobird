#include <cmath>

#include <model/zmodel_builder.h>

#include "ztext_widget.h"
#include "zwidget_builder.h"

ztext_widget::ztext_widget(const std::string& text, float unit, int layer) :
    m_width(0),
    m_height(0),
    m_unit(unit),
    zwidget(layer)
{
    set_text(text);
}

ztext_widget::~ztext_widget()
{
}

void ztext_widget::set_text(const std::string& text)
{
    const bool rebuild = m_text != text;
    m_text = text;
    if(rebuild) {
        rebuild_text_coord();
    }
}

const std::string& ztext_widget::get_text() const
{
    return m_text;
}

bool ztext_widget::input(touch_event type)
{
    return false;
}

void ztext_widget::update(size_t ms)
{
}

zrect ztext_widget::get_rect() const
{
    zvec2 position = get_position();
    zrect rect(zpoint{static_cast<int>(position.x), static_cast<int>(position.y)}, m_width, m_height);
    return rect;
}

void ztext_widget::rebuild_text_coord()
{
    m_height = m_unit;
    m_width  = m_text.size() * m_height;

    zwidget_builder::generate_text_geom(m_text, m_width, m_height, get_textured_geom_ref());
    zwidget_builder::generate_text_coord(m_text, get_textured_coord_ref());
}
