#include <model/zmodel_builder.h>

#include "zcolor_widget.h"

zcolor_widget::zcolor_widget(const zcolor& color, float width, float height, int layer) :
    zwidget(layer)
{
     set_color(color);
     zmodel_builder::generate_rect_model(width, height, get_geom_ref());
     zmodel_builder::generate_rect_aabb(width, height, get_aabb_ref());
}

zcolor_widget::~zcolor_widget()
{
}

void zcolor_widget::update(size_t ms)
{
}
