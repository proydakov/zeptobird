#include <sdl2_application.h>

#include <common/zclock.h>
#include <game/zrecord.h>
#include <scene/game/zgame_scene.h>
#include <render/impl/zgles2_render.h>

struct train_application final
{
    train_application(zplatform& platform, int w, int h, cmd_options const&)
        : m_time(get_millis())
        , m_record(platform.get_resource())
        , m_game(platform.get_sound(), m_record)
        , m_render(platform.get_resource())
    {
        zsize const size{w, h};
        m_render.resize(size);
        m_render.set_scene_size(m_game.get_size());
    }

    void update()
    {
        auto now = get_millis();
        auto delta = now - m_time;
        m_game.update(delta);
        m_time = now;
    }

    void render()
    {
        m_game.render(m_render);
        m_render.render();
    }

    void resize(int w, int h)
    {
        zsize const size{w, h};
        m_render.resize(size);
    }

    void input(touch_event, int, int)
    //void input(touch_event e, int x, int y)
    {
        //m_game.input(e, x, y);
    }

    bool is_done() const
    {
        return m_game.is_done();
    }

    int get_result() const
    {
        return m_game.get_score();
    }

    ztime m_time;
    zrecord m_record;
    zgame_scene m_game;
    zgles2_render m_render;
};

int main(int argc, char* argv[])
{
    return sdl2_main<train_application>(argc, argv);
}
