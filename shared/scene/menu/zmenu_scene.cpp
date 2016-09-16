#include <random>
#include <iostream>
#include <algorithm>

#include <render/irender.h>
#include <platform/isound.h>
#include <ui/ztext_widget.h>

#include <ui/zinput.h>
#include <ui/zcolor_widget.h>

#include <scene/zscene_invisible_object.h>

#include "zmenu_scene.h"
#include "zmenu_scene_block.h"

namespace {
const std::string MENU_THEME_MUSIC = "menu";

const zcolor BACKGROUND_COLOR{0.65, 0.65, 0.65};

const int SCENE_SIZE = 100;

const std::vector<std::string> ABOUT_TEXT = {
    "HELLO                    ",
    "I AM EVGENY PROYDAKOV    ",
    "C++ DEVELOPER            ",
    "MY PASSION IS VIDEO GAMES",
    "                         ",
    "I WANT TO JOIN ZEPTOTEAM "
};

const std::vector<std::string> RECORD_TEXT = {
    "1.MARIO:             5000",
    "2.GORDON FREEMAN:    3750",
    "3.MASTER CHIEF:      2750",
    "4.LARA CROFT:        1750",
    "5.UNKNOWN HERO          0"
};

}

zmenu_scene::zmenu_scene(isound* sound) :
    m_sound(sound),
    m_border_style( new zstyle{ zcolor{ 0x00 / 255.0, 0x64 / 255.0, 0x00 / 255.0 }, zcolor{ 0xFF / 255.0, 0xFF / 255.0, 0x00 / 255.0 } } ),
    m_body_style( new zstyle{ zcolor{ 0x00 / 255.0, 0x00 / 255.0, 0x00 / 255.0 }, zcolor{ 0x00 / 255.0, 0x00 / 255.0, 0x00 / 255.0 } } ),
    m_background_color(BACKGROUND_COLOR),
    m_done(false)
{
    std::cout << "zmenu_scene" << std::endl;

    m_widgets.reserve(16);
    init_ui();

    m_input.reset(new zinput(m_widgets));

    m_objects.reserve(1024);
    init_scene();
    init_objects();

    m_sound->play_music(MENU_THEME_MUSIC);
}

zmenu_scene::~zmenu_scene()
{
    std::cout << "~zmenu_scene" << std::endl;
}

void zmenu_scene::input(touch_event type, int x, int y)
{
    m_input->input(type, x, y);
}

void zmenu_scene::update(ztime ms)
{
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->update(ms);
        auto position = m_objects[i]->get_position();
        if(position.x < -SCENE_SIZE) {
            position.x = SCENE_SIZE;
            m_objects[i]->set_position(position);
        }
        else if(position.x > SCENE_SIZE) {
            position.x = -SCENE_SIZE;
            m_objects[i]->set_position(position);
        }
    }
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->update(ms);
    }
}

void zmenu_scene::render(irender* render) const
{
    render->set_background_color(m_background_color);
    for(size_t i = 0; i < m_objects.size(); i++) {
        m_objects[i]->render(render);
    }
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->render(render);
    }
}

zsize zmenu_scene::get_size() const
{
    zsize size{SCENE_SIZE, SCENE_SIZE};
    return size;
}

bool zmenu_scene::is_done() const
{
    return m_done;
}

void zmenu_scene::init_ui()
{
    init_main_ui();
    init_record_ui();
    init_about_ui();

    std::for_each(m_record_group.begin(), m_record_group.end(), [](zwidget* widget){
        widget->set_visible(false);
    });

    std::for_each(m_about_group.begin(), m_about_group.end(), [](zwidget* widget){
        widget->set_visible(false);
    });
}

void zmenu_scene::init_main_ui()
{
    // logo
    {
        std::unique_ptr<zwidget> logo_widget(new ztext_widget("ZEPTOBIRD", 9, 5));
        m_main_group.push_back(logo_widget.get());

        logo_widget->set_position(zvec2{0, 35});
        m_widgets.push_back(std::move(logo_widget));
    }
    // record button
    {
        const zvec2 revord_button_pos{-50, 0};
        {
            auto color_ptr = new zcolor_widget(*m_border_style.get(), 35, 15, 5);
            m_main_group.push_back(color_ptr);

            std::unique_ptr<zwidget> border_widget(color_ptr);
            border_widget->set_position(revord_button_pos);
            m_widgets.push_back(std::move(border_widget));

            std::function<void()> callback([this](){
                std::cout << "record" << std::endl;

                std::vector<zwidget*>& main_block = this->m_main_group;
                std::for_each(main_block.begin(), main_block.end(), [](zwidget* widget){
                    widget->set_visible(false);
                });

                std::vector<zwidget*>& about_block = this->m_record_group;
                std::for_each(about_block.begin(), about_block.end(), [](zwidget* widget){
                    widget->set_visible(true);
                });
            });
            color_ptr->set_release_callback(callback);
        }
        {
            std::unique_ptr<zwidget> body_widget(new zcolor_widget(*m_body_style.get(), 30, 10, 6));
            m_main_group.push_back(body_widget.get());

            body_widget->set_position(revord_button_pos);
            m_widgets.push_back(std::move(body_widget));
        }
        {
            std::unique_ptr<zwidget> record_widget(new ztext_widget("Record", 4.5, 7));
            m_main_group.push_back(record_widget.get());

            record_widget->set_position(revord_button_pos);
            m_widgets.push_back(std::move(record_widget));
        }
    }
    // play button
    {
        const zvec2 play_button_pos{0, 0};
        {
            auto color_ptr = new zcolor_widget(*m_border_style.get(), 40, 20, 5);
            m_main_group.push_back(color_ptr);

            std::unique_ptr<zwidget> border_widget(color_ptr);
            border_widget->set_position(play_button_pos);
            m_widgets.push_back(std::move(border_widget));

            std::function<void()> callback([this](){
                this->m_done = true;
            });
            color_ptr->set_release_callback(callback);
        }
        {
            std::unique_ptr<zwidget> body_widget(new zcolor_widget(*m_body_style.get(), 35, 15, 6));
            m_main_group.push_back(body_widget.get());

            body_widget->set_position(play_button_pos);
            m_widgets.push_back(std::move(body_widget));
        }
        {
            std::unique_ptr<zwidget> play_widget(new ztext_widget("PLAY", 7, 7));
            m_main_group.push_back(play_widget.get());

            play_widget->set_position(play_button_pos);
            m_widgets.push_back(std::move(play_widget));
        }
    }
    // about button
    {
        const zvec2 about_button_pos{50, 0};
        {
            auto color_ptr = new zcolor_widget(*m_border_style.get(), 35, 15, 5);
            m_main_group.push_back(color_ptr);

            std::unique_ptr<zwidget> border_widget(color_ptr);
            border_widget->set_position(about_button_pos);
            m_widgets.push_back(std::move(border_widget));

            std::function<void()> callback([this](){
                std::cout << "about" << std::endl;

                std::vector<zwidget*>& main_block = this->m_main_group;
                std::for_each(main_block.begin(), main_block.end(), [](zwidget* widget){
                    widget->set_visible(false);
                });

                std::vector<zwidget*>& about_block = this->m_about_group;
                std::for_each(about_block.begin(), about_block.end(), [](zwidget* widget){
                    widget->set_visible(true);
                });
            });
            color_ptr->set_release_callback(callback);
        }
        {
            std::unique_ptr<zwidget> body_widget(new zcolor_widget(*m_body_style.get(), 30, 10, 6));
            m_main_group.push_back(body_widget.get());

            body_widget->set_position(about_button_pos);
            m_widgets.push_back(std::move(body_widget));
        }
        {
            std::unique_ptr<zwidget> about_widget(new ztext_widget("About", 4.5, 7));
            m_main_group.push_back(about_widget.get());

            about_widget->set_position(about_button_pos);
            m_widgets.push_back(std::move(about_widget));
        }
    }
    // author
    {
        std::unique_ptr<zwidget> author_widget(new ztext_widget("(c)E.PROYDAKOV@GMAIL.COM", 5, 5));
        m_main_group.push_back(author_widget.get());

        author_widget->set_position(zvec2{0, -45});
        m_widgets.push_back(std::move(author_widget));
    }
}

void zmenu_scene::init_record_ui()
{
    // logo
    {
        std::unique_ptr<zwidget> logo_widget(new ztext_widget("Record", 9, 5));
        m_record_group.push_back(logo_widget.get());

        logo_widget->set_position(zvec2{0, 35});
        m_widgets.push_back(std::move(logo_widget));
    }
    // text
    {
        const float text_unit(4.5);
        const zvec2 top_position(0, RECORD_TEXT.size() / 2 * text_unit);
        for(size_t i = 0; i < RECORD_TEXT.size(); i++) {
            std::unique_ptr<zwidget> text_widget(new ztext_widget(RECORD_TEXT[i], text_unit, 7));
            m_record_group.push_back(text_widget.get());

            zvec2 text_position(top_position);
            text_position.y -= i * text_unit;
            text_widget->set_position(text_position);
            m_widgets.push_back(std::move(text_widget));
        }
    }
    // back button
    {
        const zvec2 back_button_pos{0, -30};
        {
            auto color_ptr = new zcolor_widget(*m_border_style.get(), 35, 15, 5);
            m_record_group.push_back(color_ptr);

            std::unique_ptr<zwidget> border_widget(color_ptr);
            border_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(border_widget));

            std::function<void()> callback([this](){
                std::cout << "back" << std::endl;

                std::vector<zwidget*>& main_block = this->m_main_group;
                std::for_each(main_block.begin(), main_block.end(), [](zwidget* widget){
                    widget->set_visible(true);
                });

                std::vector<zwidget*>& about_block = this->m_record_group;
                std::for_each(about_block.begin(), about_block.end(), [](zwidget* widget){
                    widget->set_visible(false);
                });
            });
            color_ptr->set_release_callback(callback);
        }
        {
            std::unique_ptr<zwidget> body_widget(new zcolor_widget(*m_body_style.get(), 30, 10, 6));
            m_record_group.push_back(body_widget.get());

            body_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(body_widget));
        }
        {
            std::unique_ptr<zwidget> back_widget(new ztext_widget("Back", 4.5, 7));
            m_record_group.push_back(back_widget.get());

            back_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(back_widget));
        }
    }
}

void zmenu_scene::init_about_ui()
{
    // logo
    {
        std::unique_ptr<zwidget> logo_widget(new ztext_widget("About", 9, 5));
        m_about_group.push_back(logo_widget.get());

        logo_widget->set_position(zvec2{0, 35});
        m_widgets.push_back(std::move(logo_widget));
    }
    // text
    {
        const float text_unit(4.5);
        const zvec2 top_position(0, ABOUT_TEXT.size() / 2 * text_unit);
        for(size_t i = 0; i < ABOUT_TEXT.size(); i++) {
            std::unique_ptr<zwidget> text_widget(new ztext_widget(ABOUT_TEXT[i], text_unit, 7));
            m_about_group.push_back(text_widget.get());

            zvec2 text_position(top_position);
            text_position.y -= i * text_unit;
            text_widget->set_position(text_position);
            m_widgets.push_back(std::move(text_widget));
        }
    }
    // back button
    {
        const zvec2 back_button_pos{0, -30};
        {
            auto color_ptr = new zcolor_widget(*m_border_style.get(), 35, 15, 5);
            m_about_group.push_back(color_ptr);

            std::unique_ptr<zwidget> border_widget(color_ptr);
            border_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(border_widget));

            std::function<void()> callback([this](){
                std::cout << "back" << std::endl;

                std::vector<zwidget*>& main_block = this->m_main_group;
                std::for_each(main_block.begin(), main_block.end(), [](zwidget* widget){
                    widget->set_visible(true);
                });

                std::vector<zwidget*>& about_block = this->m_about_group;
                std::for_each(about_block.begin(), about_block.end(), [](zwidget* widget){
                    widget->set_visible(false);
                });
            });
            color_ptr->set_release_callback(callback);
        }
        {
            std::unique_ptr<zwidget> body_widget(new zcolor_widget(*m_body_style.get(), 30, 10, 6));
            m_about_group.push_back(body_widget.get());

            body_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(body_widget));
        }
        {
            std::unique_ptr<zwidget> back_widget(new ztext_widget("Back", 4.5, 7));
            m_about_group.push_back(back_widget.get());

            back_widget->set_position(back_button_pos);
            m_widgets.push_back(std::move(back_widget));
        }
    }
}

void zmenu_scene::init_scene()
{
    std::unique_ptr<iscene_object> aabb( new zscene_invisible_object( SCENE_SIZE - 2, SCENE_SIZE - 2, 0 ) );
    aabb->set_position(zvec2(0, 0));
    m_objects.push_back(std::move(aabb));
}

void zmenu_scene::init_objects()
{
    std::vector<zvec2> speeds{
        zvec2{+31, 0},
        zvec2{-29, 0},
        zvec2{+15, 0},
        zvec2{-11, 0}
    };

    std::vector<zcolor> colors{
        zcolor{0xFF / 255.0, 0x8C / 255.0, 0x00 / 255.0},
        zcolor{0x00 / 255.0, 0xBF / 255.0, 0xFF / 255.0},
        zcolor{0xDC / 255.0, 0x14 / 255.0, 0x3C / 255.0},
        zcolor{0x99 / 255.0, 0x32 / 255.0, 0xCC / 255.0},
        zcolor{0xAD / 255.0, 0xFF / 255.0, 0x2F / 255.0}
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> position_dis(-SCENE_SIZE, SCENE_SIZE);
    std::uniform_int_distribution<size_t> speed_dis(0, speeds.size() - 1);
    std::uniform_int_distribution<size_t> color_dis(0, colors.size() - 1);

    for(int i = -250; i < 0; i++) {
        zvec2 position( position_dis(gen), position_dis(gen) );
        zvec2 speed( speeds[ speed_dis(gen) ] );
        zcolor color( colors[ color_dis(gen) ] );

        std::unique_ptr<zmenu_scene_block> block(new zmenu_scene_block(20, 10, color, i));
        block->set_position(position);
        block->set_speed(speed);
        m_objects.push_back(std::move(block));

    }
}
