#pragma once

#include <memory>
#include <vector>

#include <scene/iscene.h>
#include <render/zcolor.h>

class isound;
class irender;
class zwidget;
class iscene_object;

class zmenu_scene final : public iscene
{
public:
    zmenu_scene(isound* sound);
    ~zmenu_scene() override;

    void input() override;
    void update(ztime ms) override;
    void render(irender* render) const override;

    zsize get_size() const override;

    bool is_done() const override;

private:
    isound* m_sound;

    std::vector<std::unique_ptr<iscene_object>> m_objects;
    std::vector<std::unique_ptr<zwidget>> m_widgets;

    zcolor m_background_color;
    bool   m_done;
};
