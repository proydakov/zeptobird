#pragma once

#include <ui/zwidget.h>

class zcolor_widget : public zwidget
{
public:
    zcolor_widget(const zcolor& color, float width, float height, int layer);
    ~zcolor_widget() override;

    void update(size_t ms) override;
};
