#pragma once

#include <functional>

#include <ui/zstyle.h>
#include <ui/zwidget.h>

class zcolor_widget : public zwidget
{
public:
    zcolor_widget(const zstyle& style, float width, float height, int layer);
    ~zcolor_widget() override;

    bool input(touch_event type) override;
    void update(ztime ms) override;
    zrect get_rect() const override;

    void set_release_callback(const std::function<void()>& callback);

private:
    const zstyle& m_style;

    float m_width;
    float m_height;

    bool m_call_callback;
    std::function<void()> m_callback;
};
