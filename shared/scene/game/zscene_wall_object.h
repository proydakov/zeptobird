#pragma once

#include <memory>
#include <scene/iscene_object.h>

class zmodel;
class zworld;
class zrect_body;

class zscene_wall_object : public iscene_object
{
public:
    zscene_wall_object(zworld* world, float width, float height, int layer);
    ~zscene_wall_object() override;

    void update(ztime ms) override;
    void render(irender* render) const override;

    const zvec2& get_position() const override;
    void set_position(const zvec2& position) override;

    const zvec2& get_speed() const override;
    void set_speed(const zvec2& speed) override;

    void set_size(zfloat width, zfloat height);

private:
    std::unique_ptr<zrect_body> m_body;
    std::unique_ptr<zmodel>     m_model;
};
