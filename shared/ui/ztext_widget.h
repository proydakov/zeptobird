#pragma once

#include <string>

#include <ui/zwidget.h>

class ztext_widget : public zwidget
{
public:
    ztext_widget(const std::string& text, float unit, int layer);
    ~ztext_widget() override;

    void set_text(const std::string& text);
    const std::string& get_text() const;

    void update(size_t ms) override;

private:
    void rebuild_text_coord();

private:
    float m_unit;
    std::string m_text;
};
