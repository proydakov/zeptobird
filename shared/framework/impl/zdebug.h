#pragma once

#include <memory>
#include <framework/impl/idebug.h>

class ztext_widget;
class zfps_calculator;

class zdebug : public idebug
{
public:
    zdebug(irender* render);
    ~zdebug() override;

    void update(size_t ms) override;
    void render(irender* render) override;

private:
    irender* m_render;

    std::unique_ptr<zfps_calculator> m_fps_calculator;
    std::unique_ptr<ztext_widget> m_fps_widget;
    std::unique_ptr<ztext_widget> m_vert_widget;
};
