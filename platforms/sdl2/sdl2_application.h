#include <sdl2_sound.h>
#include <fake_sound.h>
#include <sdl2_resource.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <variant>
#include <iostream>
#include <functional>

#include <common/zinput.h>
#include <platform/zplatform.h>

class keyboard_press_guard
{
public:
    keyboard_press_guard(SDL_Keycode code, std::function<void()> lambda);
    void operator()(SDL_Event const& Event);

private:
    SDL_Keycode const m_code;
    bool m_lock;
    std::function<void()> m_lambda;
};

struct cmd_options
{
    bool has_sound;
    std::string ai_model;
};

cmd_options parse_cmd_options(int argc, char* argv[]);

void trace_info();

template<typename T>
int sdl2_main(int argc, char* argv[])
{
    int width = 1200;
    int height = 700;

    auto const cmd_opt = parse_cmd_options(argc, argv);

    const std::uint32_t options = SDL_INIT_VIDEO | (cmd_opt.has_sound ? SDL_INIT_AUDIO : 0);

    SDL_Init(options);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    constexpr std::uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    SDL_Window* window = SDL_CreateWindow("SDL2", 0, 0, width, height, flags);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    trace_info();

    int result = EXIT_SUCCESS;

    {
        bool running = true;
        bool fullscreen = false;

        auto fs_functor = keyboard_press_guard(SDLK_F11, [window, &fullscreen](){
            fullscreen = !fullscreen;
            std::uint32_t const new_flags = fullscreen ? (flags | SDL_WINDOW_FULLSCREEN) : flags;
            SDL_SetWindowFullscreen(window, new_flags);
        });

        std::variant<std::monostate, sdl2_sound, fake_sound> sound;
        
        sdl2_resource resource;
        
        zplatform platform(cmd_opt.has_sound ?
                reinterpret_cast<isound&>(sound.emplace<sdl2_sound>()) :
                reinterpret_cast<isound&>(sound.emplace<fake_sound>()),
            resource);

        T application(platform, width, height, cmd_opt);

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    application.input(touch_event::began, event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEBUTTONUP:
                    application.input(touch_event::end, event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEMOTION:
                    application.input(touch_event::move, event.motion.x, event.motion.y);
                    break;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;

                        case SDLK_F11:
                            fs_functor(event);
                            break;
                    }
                    break;

                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        auto width = size_t(event.window.data1);
                        auto height = size_t(event.window.data2);
                        application.resize(width, height);
                    }
                        break;
                    }
                    break;

                case SDL_QUIT:
                    running = false;
                    break;
                }
            }

            application.update();
            application.render();

            running &= !application.is_done();

            SDL_GL_SwapWindow(window);
        }

        result = application.get_result();
    }

    SDL_GL_DeleteContext(context); 
    SDL_DestroyWindow(window);
    SDL_Quit();

    return result;
}

