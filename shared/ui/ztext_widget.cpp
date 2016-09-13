#include <cmath>

#include <model/zmodel_builder.h>

#include "ztext_widget.h"
#include "zwidget_builder.h"

ztext_widget::ztext_widget(const std::string& text, float unit, int layer) :
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

void ztext_widget::update(size_t ms)
{
}

void ztext_widget::rebuild_text_coord()
{
    const float height = m_unit;
    const float width  = m_text.size() * height;

    zwidget_builder::generate_text_geom(m_text, width, height, get_textured_geom_ref());
    zwidget_builder::generate_text_coord(m_text, get_textured_coord_ref());
}
