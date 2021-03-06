#pragma once

#include <string>

#include <ui/zwidget.h>

class ztext_widget : public zwidget
{
public:
    ztext_widget(const std::string& text, float unit, int layer);
    ztext_widget(const std::string& text, float unit, int layer, std::unique_ptr<ianimation>&& animator);
    ~ztext_widget() override;

    void set_text(const std::string& text);
    const std::string& get_text() const;

    bool input(touch_event type) override;

private:
    zrect get_rect_impl() const override;
    void rebuild_text_coord();

private:
    float m_width;
    float m_height;

    float m_unit;
    std::string m_text;
};
