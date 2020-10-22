#pragma once

#include <memory>
#include <scene/iscene_object.h>

class ibody;
class zmodel;
class zworld;

class zscene_coin_object final : public iscene_object
{
public:
    zscene_coin_object(zworld& world, float radius, int layer);
    ~zscene_coin_object() override;

    void update(ztime ms) override;
    void render(irender& render) const override;

    const zvec2& get_position() const override;
    void set_position(const zvec2& position) override;

    const zvec2& get_speed() const override;
    void set_speed(const zvec2& speed) override;

    void set_active(bool active);

private:
    std::unique_ptr<ibody>  m_body;
    std::unique_ptr<zmodel> m_model;
};
