#pragma once

#include <memory>
#include <scene/iscene_object.h>

class imodel;

class zscene_invisible_object : public iscene_object
{
public:
    zscene_invisible_object(float width, float height);
    ~zscene_invisible_object() override;

    void update(size_t ms) override;
    void render(irender* render) const override;

    const zvec2& get_position() const override;
    void set_position(const zvec2& position) override;

    const zvec2& get_speed() const override;
    void set_speed(const zvec2& speed) override;

private:
    std::unique_ptr<imodel> m_model;
    zvec2 m_position;
    zvec2 m_speed;
};