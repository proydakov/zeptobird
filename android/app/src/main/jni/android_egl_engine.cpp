#include <cassert>
#include <iostream>

#include <EGL/egl.h>
#include <android_native_app_glue.h>

#include "android_egl_engine.h"

struct android_egl_engine::d
{
    d() :
            app(nullptr),
            display(nullptr),
            surface(nullptr),
            context(nullptr),
            config(nullptr),
            width(0),
            height(0)
    {
    }

    ~d()
    {
        app    = nullptr;
        display = nullptr;
        surface = nullptr;
        context = nullptr;
        config = nullptr;

        width  = 0;
        height = 0;
    }

    android_app* app;

    EGLDisplay   display;
    EGLSurface   surface;
    EGLContext   context;
    EGLConfig    config;

    EGLint       width;
    EGLint       height;
};

android_egl_engine::android_egl_engine(android_app* app)
{
    m_d.reset(new d());
    m_d->app = app;

    init_display();
    init_surface();
    init_context();

    // bind them
    if (EGL_FALSE == eglMakeCurrent(m_d->display, m_d->surface, m_d->surface, m_d->context)) {
        std::cout << "NativeEngine: eglMakeCurrent failed, EGL error " << eglGetError() << std::endl;
    }

    EGLint w, h;

    eglQuerySurface(m_d->display, m_d->surface, EGL_WIDTH,  &w);
    eglQuerySurface(m_d->display, m_d->surface, EGL_HEIGHT, &h);

    m_d->width  = w;
    m_d->height = h;
}

android_egl_engine::~android_egl_engine()
{
    if (m_d->display != EGL_NO_DISPLAY) {

        eglMakeCurrent(m_d->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_d->context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_d->display, m_d->context);
        }
        if (m_d->surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_d->display, m_d->surface);
        }
        eglTerminate(m_d->display);
    }

    m_d->display = EGL_NO_DISPLAY;
    m_d->context = EGL_NO_CONTEXT;
    m_d->surface = EGL_NO_SURFACE;
}

int android_egl_engine::get_width() const
{
    return m_d->width;
}

int android_egl_engine::get_height() const
{
    return m_d->height;
}

bool android_egl_engine::swap_buffers()
{
    if (EGL_FALSE == eglSwapBuffers(m_d->display, m_d->surface)) {
        // failed to swap buffers...
        std::cout << "NativeEngine: eglSwapBuffers failed, EGL error " << eglGetError() << std::endl;
        handle_egl_error(eglGetError());
        return false;
    }
    return true;
}

bool android_egl_engine::init_display()
{
    if (m_d->display != EGL_NO_DISPLAY) {
        // nothing to do
        std::cout << "NativeEngine: no need to init display (already had one)." << std::endl;
        return true;
    }

    std::cout << "NativeEngine: initializing display." << std::endl;
    m_d->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(m_d->display, 0, 0)) {
        std::cout << "NativeEngine: failed to init display, error " << eglGetError() << std::endl;
        return false;
    }
    return true;
}

bool android_egl_engine::init_surface()
{
    // need a display
    assert(m_d->display != EGL_NO_DISPLAY);

    if (m_d->surface != EGL_NO_SURFACE) {
        // nothing to do
        std::cout << "NativeEngine: no need to init surface (already had one)." << std::endl;
        return true;
    }

    std::cout << "NativeEngine: initializing surface." << std::endl;

    EGLint numConfigs;

    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, // request OpenGL ES 2.0
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE
    };

    // since this is a simple sample, we have a trivial selection process. We pick
    // the first EGLConfig that matches:
    eglChooseConfig(m_d->display, attribs, &m_d->config, 1, &numConfigs);

    // create EGL surface
    m_d->surface = eglCreateWindowSurface(m_d->display, m_d->config, m_d->app->window, NULL);
    if (m_d->surface == EGL_NO_SURFACE) {
        std::cout << "Failed to create EGL surface, EGL error " << eglGetError() << std::endl;
        return false;
    }

    std::cout << "NativeEngine: successfully initialized surface." << std::endl;
    return true;
}

bool android_egl_engine::init_context()
{
    // need a display
    assert(m_d->display != EGL_NO_DISPLAY);

    EGLint attribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE }; // OpenGL 2.0

    if (m_d->context != EGL_NO_CONTEXT) {
        // nothing to do
        std::cout << "NativeEngine: no need to init context (already had one)." << std::endl;
        return true;
    }

    std::cout << "NativeEngine: initializing context." << std::endl;

    // create EGL context
    m_d->context = eglCreateContext(m_d->display, m_d->config, NULL, attribList);
    if (m_d->context == EGL_NO_CONTEXT) {
        std::cout << "Failed to create EGL context, EGL error " << eglGetError() << std::endl;
        return false;
    }

    std::cout << "NativeEngine: successfull initialized context." << std::endl;

    return true;
}

bool android_egl_engine::handle_egl_error(EGLint error)
{
    switch (error) {
        case EGL_SUCCESS:
            // nothing to do
            return true;
        case EGL_CONTEXT_LOST:
            std::cout << "NativeEngine: egl error: EGL_CONTEXT_LOST. Recreating context." << std::endl;
            //KillContext();
            return true;
        case EGL_BAD_CONTEXT:
            std::cout << "NativeEngine: egl error: EGL_BAD_CONTEXT. Recreating context." << std::endl;
            //KillContext();
            return true;
        case EGL_BAD_DISPLAY:
            std::cout << "NativeEngine: egl error: EGL_BAD_DISPLAY. Recreating display." << std::endl;
            //KillDisplay();
            return true;
        case EGL_BAD_SURFACE:
            std::cout << "NativeEngine: egl error: EGL_BAD_SURFACE. Recreating display." << std::endl;
            //KillSurface();
            return true;
        default:
            std::cout << "NativeEngine: unknown egl error: " << error << std::endl;
            return false;
    }
}
