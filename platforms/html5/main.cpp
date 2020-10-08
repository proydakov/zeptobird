#include <iostream>

#include <sdl_ctx.h>
#include <emscripten.h>

#include <html5_sound.h>
#include <html5_resource.h>
#include <framework/zframework.h>

sdl_ctx*    stage = nullptr;
zframework* framework = nullptr;

void handleEvent(SDL_Event& event)
{
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        framework->input(touch_event::began, event.motion.x, event.motion.y);
        break;

    case SDL_MOUSEBUTTONUP:
        framework->input(touch_event::end, event.motion.x, event.motion.y);
        break;

    case SDL_MOUSEMOTION:
        framework->input(touch_event::move, event.motion.x, event.motion.y);
        break;
    }
}

void init(size_t width, size_t height)
{
    framework->init(width, height);
}

void render(SDL_Surface* screen)
{
    framework->update();
    framework->render();

    SDL_GL_SwapBuffers();
}

void update(int deltaTime)
{
    if(deltaTime > 1000) {
        std::cout << "pause" << std::endl;
        framework->pause();
    }
}

void step()
{
    stage->step();
}

int main (int argc, char** argv)
{
    int w = EM_ASM_INT({
        var canvas = document.getElementById('canvas');
        return canvas.width;
    }, 0);

    int h = EM_ASM_INT({
        var canvas = document.getElementById('canvas');
        return canvas.height;
    }, 0);

    std::cout << "screen w: " << w << " h: " << h << std::endl;
    h = std::min(w, h);
    std::cout << "viewport w: " << w << " h: " << h << std::endl;

    const int frame_rate = 60;
    const size_t width  = w;
    const size_t height = h;

    stage = new sdl_ctx(width, height, frame_rate, SDL_OPENGL | SDL_RESIZABLE);

    html5_sound sound;
    html5_resource resource;
    zplatform platform(sound, resource);

    framework = new zframework(platform);

    init(width, height);

    stage->setCaption("ZeptoBird");
    stage->setEventListener(&handleEvent);
    stage->setRenderCallback(&render);
    stage->setUpdateCallback(&update);

    emscripten_set_main_loop(step, 0, true);

    delete stage;
    delete framework;

    return 0;
}
