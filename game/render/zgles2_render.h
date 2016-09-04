#pragma once

#include <memory>
#include <render/irender.h>

class zgles2_render : public irender
{
public:
    zgles2_render();
    virtual ~zgles2_render() override;

    void init(const iresource* resource, int width, int height) override;
    void deinit() override;

    void render() override;

    void input() override;

private:
    bool load_shaders(const iresource* resource);

private:
    struct data;
    std::unique_ptr<data> m_data;
};
