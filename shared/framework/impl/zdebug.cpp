#include <sstream>
#include <iomanip>
#include <cassert>

#include <render/irender.h>

#include "zdebug.h"
#include "zfps_calculator.h"

#include <ui/ztext_widget.h>

namespace {

const float COUNTER_UNIT  = 2.5;
const int   COUNTER_LAYER = 9;

std::string build_fps_text(float fps)
{
    char buffer[10];
    snprintf(buffer, std::size(buffer), "FPS:%5.1f", fps);
    std::string fps_str( buffer );
    return fps_str;
}

std::string build_vertex_text(size_t vertex)
{
    std::stringstream sstream;
    sstream << "VER:" << std::setw(5) << vertex;
    return sstream.str();
}

}

zdebug::zdebug(irender* render) :
    m_render(render),
    m_fps_calculator(new zfps_calculator()),
    m_fps_widget(new ztext_widget(build_fps_text(m_fps_calculator->get_fps()), COUNTER_UNIT, COUNTER_LAYER)),
    m_vert_widget(new ztext_widget(build_vertex_text(render->get_vertex_statistic()), COUNTER_UNIT, COUNTER_LAYER))
{
    ztext_widget* fps_widget = m_fps_widget.get();
    ztext_widget* vert_widget = m_vert_widget.get();

    std::function<void(const zsize&)> size_change([fps_widget, vert_widget](const zsize& size) {
        float xfps = -1 * size.width / 2 + COUNTER_UNIT * 5;
        float yfps = size.height / 2 - COUNTER_UNIT;
        fps_widget->set_position(zvec2{xfps, yfps});

        float xvetx = -1 * size.width / 2 + COUNTER_UNIT * 5;
        float yvetx = size.height / 2 - COUNTER_UNIT * 2;
        vert_widget->set_position(zvec2{xvetx, yvetx});
    });
    render->set_scene_size_change_callback(size_change);

    render->set_aabb_visible(false);
}

zdebug::~zdebug()
{
}

void zdebug::update(size_t ms)
{
    m_fps_calculator->update(ms);
    m_fps_widget->set_text(build_fps_text(m_fps_calculator->get_fps()));

    m_vert_widget->update(ms);
    m_vert_widget->set_text(build_vertex_text(m_render->get_vertex_statistic()));
}

void zdebug::render(irender* render)
{
    assert(m_render == render);
    render->render(m_fps_widget.get(), m_fps_widget->get_position(), m_fps_widget->get_rotation(), m_fps_widget->get_scale());
    render->render(m_vert_widget.get(), m_vert_widget->get_position(), m_vert_widget->get_rotation(), m_vert_widget->get_scale());
}
