#include <sdl2_application.h>

cmd_options parse_cmd_options(int argc, char* argv[])
{
    cmd_options opt { true, "" };

    for(int i = 1; i < argc; i++)
    {
        if (std::string("-nosound") == argv[i])
        {
            opt.has_sound = false;
        }
        else if (std::string("-ai") == argv[i])
        {
            i++;
            if ( i < argc)
            {
                opt.ai_model = argv[i];
            }
        }
    }

    return opt;
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

keyboard_press_guard::keyboard_press_guard(SDL_Keycode code, std::function<void()> lambda)
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
