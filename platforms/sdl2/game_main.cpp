#include <sdl2_application.h>

#include <framework/zframework.h>

struct game_application final
{
    game_application(zplatform& platform, int w, int h, cmd_options const&)
        : framework(platform, w, h)
    {
    }

    void update()
    {
        framework.update();
    }

    void render()
    {
        framework.render();
    }

    void resize(int w, int h)
    {
        framework.resize(w, h);
    }

    void input(touch_event type, int x, int y)
    {
        framework.input(type, x, y);
    }

    bool is_done() const
    {
        return false;
    }

    int get_result() const
    {
        return 0;
    }

    zframework framework;
};

int main(int argc, char* argv[])
{
    return sdl2_main<game_application>(argc, argv);
}
