#pragma once

#include <memory>
#include <vector>

#include <scene/iscene.h>
#include <render/zcolor.h>

class isound;
class iresource;

class irender;
class zwidget;
class iscene_object;

class zstyle;
class zinput;
class zrecord;

class ztext_widget;

class zmenu_scene final : public iscene
{
public:
    zmenu_scene(isound* sound, zrecord* record);
    ~zmenu_scene() override;

    void input(touch_event type, int x, int y) override;
    void update(ztime ms) override;
    void render(irender* render) const override;

    zsize get_size() const override;

    bool is_done() const override;

private:
    void init_ui();
    void init_main_ui();
    void init_record_ui();
    void init_about_ui();

    void init_scene();
    void init_objects();

private:
    isound*  m_sound;
    zrecord* m_record;

    std::unique_ptr<zstyle> m_border_style;
    std::unique_ptr<zstyle> m_body_style;

    std::vector<std::unique_ptr<iscene_object>> m_objects;
    std::vector<std::unique_ptr<zwidget>> m_widgets;

    std::vector<zwidget*> m_main_group;
    std::vector<zwidget*> m_record_group;
    std::vector<zwidget*> m_about_group;

    std::vector<ztext_widget*> m_record_table;

    std::unique_ptr<zinput> m_input;

    zcolor m_background_color;
    bool   m_done;
};
