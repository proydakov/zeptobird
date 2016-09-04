#pragma once

#include <memory>

#include <scene/iscene_object.h>

class ibody;
class imodel;
class zworld;

class zscene_wall_object : public iscene_object
{
public:
    zscene_wall_object(zworld* world);
    ~zscene_wall_object() override;

    void update(size_t ms) override;
    void render(irender* render) const override;

    const zvec2& get_position() const override;
    void set_position(const zvec2& position) override;

private:
    std::unique_ptr<ibody>  m_body;
    std::unique_ptr<imodel> m_model;
};
