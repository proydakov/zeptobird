#pragma once

#include <memory>
#include <render/irender.h>

// Export impl class
class zgles2_render final : public irender
{
public:
    zgles2_render(const iresource* resource);
    virtual ~zgles2_render() override;

    void init(const zsize& view_size, float angle) override;
    void deinit() override;

    void prepare() override;
    void render(const imodel* model, const zvec2& position, zfloat rotation, zfloat scale) override;
    void render(const iwidget* widget, const zvec2& position, zfloat rotation, zfloat scale) override;
    void render() override;

    void set_scene_size(const zsize& scene_size) override;
    void set_background_color(const zcolor& color) override;
    void set_aabb_color(const zcolor& color) override;

private:
    bool load_shaders(const iresource* resource);
    bool load_textures(const iresource* resource);

private:
    struct data;
    std::unique_ptr<data> m_data;
};
