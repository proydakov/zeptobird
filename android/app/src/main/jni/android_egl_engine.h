#pragma once

#include <memory>

struct android_app;

class android_egl_engine final
{
public:
    android_egl_engine(android_app* app);
    ~android_egl_engine();

    bool swap_buffers();

    int get_width() const;
    int get_height() const;

private:
    bool init_display();
    bool init_surface();
    bool init_context();

    bool handle_egl_error(int error);

private:
    struct d;
    std::unique_ptr<d> m_d;
};
