/*
 * Copyright (C) Evgeny Proydakov
 */

#include <memory>
#include <iostream>

#include <android_logger.h>
#include <android_egl_engine.h>
#include <android_sound.h>
#include <android_resource.h>
#include <android_native_app_glue.h>

#include <common/zinput.h>
#include <framework/zframework.h>

extern "C" {
    void android_main(struct android_app* state);
};

struct application_data
{
    bool is_enabled;

    std::unique_ptr<android_sound>      sound;
    std::unique_ptr<android_resource>   resource;
    std::unique_ptr<android_egl_engine> egl_engine;
    std::unique_ptr<zframework>         framework;
};

static int32_t engine_handle_input(android_app* app, AInputEvent* event)
{
    application_data* app_data = (application_data*)app->userData;

    int type = AInputEvent_getType(event);

    int src = AInputEvent_getSource(event);
    int action = AMotionEvent_getAction(event);
    int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
    int ptrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

    if (type == AINPUT_EVENT_TYPE_MOTION) {
        touch_event touch_type;

        if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked == AMOTION_EVENT_ACTION_POINTER_DOWN) {
            touch_type = touch_event::began;
        }
        else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked == AMOTION_EVENT_ACTION_POINTER_UP) {
            touch_type = touch_event::end;
        }
        else {
            touch_type = touch_event::move;
        }

        float motionX = AMotionEvent_getX(event, ptrIndex);
        float motionY = AMotionEvent_getY(event, ptrIndex);

        app_data->framework->input(touch_type, motionX, motionY);

        return 1;
    }
    return 0;
}

static void engine_handle_cmd(android_app* app, int32_t cmd)
{
    application_data* app_data = (application_data*)app->userData;

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;

        case APP_CMD_INIT_WINDOW:
        {
            app_data->is_enabled = true;
            app_data->egl_engine.reset(new android_egl_engine(app));
            zplatform platform(app_data->sound.get(), app_data->resource.get());
            app_data->framework.reset(new zframework(platform));
            std::cout << "WIDTH : " << app_data->egl_engine->get_width() << std::endl;
            std::cout << "HEIGHT: " << app_data->egl_engine->get_height() << std::endl;
            app_data->framework->init(app_data->egl_engine->get_width(), app_data->egl_engine->get_height());
        }
            break;

        case APP_CMD_TERM_WINDOW:
        {
            app_data->is_enabled = false;
            app_data->framework.reset();
            app_data->egl_engine.reset();
        }
            break;

        case APP_CMD_GAINED_FOCUS:
            app_data->is_enabled = true;
            //app_data->logger->log_warning("APP_CMD_GAINED_FOCUS");
            //app_data->engine->enable();
            break;

        case APP_CMD_LOST_FOCUS:
            app_data->is_enabled = false;
            //app_data->logger->log_warning("APP_CMD_LOST_FOCUS");
            //app_data->engine->disable();
            break;
    }
}

static void draw(android_app* app)
{
    application_data* app_data = (application_data*)app->userData;
    app_data->framework->update();
    app_data->framework->render();
    app_data->egl_engine->swap_buffers();
}

void android_main(struct android_app* app)
{
    app_dummy(); // Make sure glue isn't stripped.

    start_logger("zeptobird");

    std::cout << "start main" << std::endl;

    application_data app_data{false};
    app_data.sound.reset(new android_sound);
    app_data.resource.reset(new android_resource(app->activity->assetManager));

    app->userData = &app_data;
    app->onAppCmd = engine_handle_cmd;
    app->onInputEvent = engine_handle_input;

    while (true) {
        int ident;
        int events;
        android_poll_source* source;

        while ((ident = ALooper_pollAll(app_data.is_enabled ? 0 : -1, NULL, &events, (void**)&source)) >= 0) {
            if (source != NULL) {
                source->process(app, source);
            }

            if (app->destroyRequested != 0) {
                std::cout << "finish main" << std::endl;
                return;
            }
        }
        if(app_data.is_enabled) {
            draw(app);
        }
    }
}
