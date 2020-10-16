#include <sdl2_sound.h>
#include <sdl2_resource.h>
#include <framework/zframework.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <functional>

class keyboard_press_guard
{
public:
    keyboard_press_guard(SDL_Keycode code, std::function<void()>&& lambda);
    void operator()(SDL_Event const& Event);

private:
    SDL_Keycode const m_code;
    bool m_lock;
    std::function<void()> m_lambda;
};

void trace_info();

int main(int, char*[])
{
    constexpr std::uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    int width = 1200;
    int height = 700;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow("SDL2", 0, 0, width, height, flags);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    trace_info();

    {
        sdl2_sound sound;
        sdl2_resource resource;
        
        zplatform platform(sound, resource);
        zframework framework(platform, width, height);

        bool running = true;
        bool fullscreen = false;

        auto fs_functor = keyboard_press_guard(SDLK_F11, [window, &fullscreen](){
            fullscreen = !fullscreen;
            std::uint32_t const new_flags = fullscreen ? (flags | SDL_WINDOW_FULLSCREEN) : flags;
            SDL_SetWindowFullscreen(window, new_flags);
        });

        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    framework.input(touch_event::began, event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEBUTTONUP:
                    framework.input(touch_event::end, event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEMOTION:
                    framework.input(touch_event::move, event.motion.x, event.motion.y);
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
                        framework.resize(width, height);
                    }
                        break;
                    }
                    break;

                case SDL_QUIT:
                    running = false;
                    break;
                }
            }

            framework.update();
            framework.render();

            SDL_GL_SwapWindow(window);
        }
    }

    SDL_GL_DeleteContext(context); 
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void trace_info()
{
    // SDL info
    SDL_version c;
    SDL_version l;
    SDL_VERSION( &c );
    SDL_GetVersion( &l );

    std::cout << "SDL compiled version: " << (int)c.major << "." << (int)c.minor << "." << (int)c.patch << "\n";
    std::cout << "SDL linked version  : " << (int)l.major << "." << (int)l.minor << "." << (int)l.patch << "\n";

    std::cout << "\n";

    // GL info
    std::cout << "GL_VENDOR   : " << glGetString( GL_VENDOR ) << "\n";
    std::cout << "GL_RENDERER : " << glGetString( GL_RENDERER ) << "\n";
    std::cout << "GL_VERSION  : " << glGetString( GL_VERSION ) << "\n";
    std::cout << "GLSL version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << "\n";

    std::cout << "\n";
    
    std::cout.flush();
}

keyboard_press_guard::keyboard_press_guard(SDL_Keycode code, std::function<void()>&& lambda)
    : m_code(code)
    , m_lock(false)
    , m_lambda(std::move(lambda))
{
}

void keyboard_press_guard::operator()(SDL_Event const& Event)
{
    switch (Event.type) {
    case SDL_KEYDOWN:
        if(m_code == Event.key.keysym.sym && m_lock == false)
        {
            m_lock = true;
            m_lambda();
        }
        break;

    case SDL_KEYUP:
        if(m_code == Event.key.keysym.sym && m_lock == true)
        {
            m_lock = false;
        }
        break;
    }
}
