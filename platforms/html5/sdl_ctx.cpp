#include "sdl_ctx.h"

Uint32 timer_onComplete(Uint32 interval, void *param);

sdl_ctx::sdl_ctx(int width, int height, int frameRate, int flags)
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0) {
        screen = SDL_SetVideoMode (width, height, 0, flags);
        if (screen != NULL) {
            previousTime = 0;
            ticksPerFrame = (int)(1000 / frameRate);
            active = true;
            paused = false;
        }
        else {
            std::cerr << "Could not set video mode: " << SDL_GetError () << std::endl;
        }
    }
    else {
        std::cerr << "Could not initialize SDL: " << SDL_GetError () << std::endl;
    }
}

sdl_ctx::~sdl_ctx()
{
    SDL_Quit ();
}

void sdl_ctx::handleEvent(SDL_Event &event)
{
    switch (event.type) {
        case SDL_ACTIVEEVENT:
            if (event.active.state & SDL_APPACTIVE) {
                if (event.active.gain == 0) {
                    //paused = true;
                }
                else {
                    //paused = false;
                }
            }
            break;

        case SDL_VIDEOEXPOSE:
            render();
            break;

        case SDL_WINDOWEVENT_HIDDEN:
            std::cout << "SDL_WINDOWEVENT_HIDDEN" << std::endl;
            break;

        case SDL_QUIT:
            active = false;
            break;
    }
    if (eventListener != NULL) {
        (*eventListener) (event);
    }
    event.type = -1;
}

void sdl_ctx::render()
{
    if (renderCallback != NULL) {
        (*renderCallback) (screen);
    }
}

void sdl_ctx::setCaption(const std::string& title)
{
    if (active) {
        SDL_WM_SetCaption (title.c_str (), title.c_str ());
    }
}

void sdl_ctx::setEventListener(void (*listener) (SDL_Event&))
{
    eventListener = listener;
}

void sdl_ctx::setRenderCallback(void (*callback) (SDL_Surface*))
{
    renderCallback = callback;
}

void sdl_ctx::setUpdateCallback(void (*callback) (int))
{
    updateCallback = callback;
}

void sdl_ctx::step()
{
    SDL_Event event;

    if (paused) {
        if (SDL_PollEvent (&event)) {
            handleEvent (event);
        }
    }
    else {
        while (SDL_PollEvent (&event)) {
            handleEvent (event);
            if (!active) {
                break;
            }
        }
        if (active) {
            int currentTime = SDL_GetTicks();
            int deltaTime = currentTime - previousTime;

            update (currentTime - previousTime);
            render ();

            while (deltaTime < ticksPerFrame) {
                SDL_TimerID timer = SDL_AddTimer (ticksPerFrame - deltaTime, timer_onComplete, NULL);
                SDL_PollEvent (&event);
                SDL_RemoveTimer (timer);

                if (event.type != SDL_USEREVENT) {
                    handleEvent (event);
                    deltaTime = SDL_GetTicks () - previousTime;
                }
                else {
                    event.type = -1;
                    break;
                }
            }
            previousTime = currentTime;
        }
    }
}

void sdl_ctx::update (int deltaTime)
{
    if (updateCallback != NULL) {
        (*updateCallback) (deltaTime);
    }
}

Uint32 timer_onComplete(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    return 0;
}
