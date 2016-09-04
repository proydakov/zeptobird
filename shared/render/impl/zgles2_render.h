#pragma once

#include <memory>
#include <render/irender.h>

class zgles2_render : public irender
{
public:
    zgles2_render(const iresource* resource);
    virtual ~zgles2_render() override;

    void init(int width, int height) override;
    void deinit() override;

    void render(const imodel* model, const zvec2& position) override;
    void render() override;

    void set_background_color(const zcolor& color) override;

private:
    bool load_shaders(const iresource* resource);

private:
    struct data;
    std::unique_ptr<data> m_data;
};