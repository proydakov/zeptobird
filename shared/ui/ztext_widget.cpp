#include "string.h"

#include "ztext_widget.h"

namespace {
    const int TEXT_HEIGHT = 7;
    const int TEXT_WIDTH  = 5;
}

ztext_widget::ztext_widget(const std::string& text, int layer) :
    zwidget(layer)
{
    set_text(text);
}

ztext_widget::~ztext_widget()
{
}

void ztext_widget::set_text(const std::string& text)
{
    m_text = text;
    rebuild_text_coord();
}

const std::string& ztext_widget::get_text() const
{
    return m_text;
}

void ztext_widget::update(size_t ms)
{
    
}

void ztext_widget::rebuild_text_coord()
{
    /*
    m_texture.resize(0);
    m_texture.reserve(TEXT_HEIGHT * TEXT_WIDTH);

    const char ALPHABET_ART[] = {
        "+---+" // chr 65, A
        "|   |"
        "|   |"
        "+---+"
        "|   |"
        "|   |"
        "+   +"
    };

    const size_t length = strlen(ALPHABET_ART);

    // Image, 3 bytes per pixel (R, G, B)
    for(int i = 0, p = 0; i < length; i++, p += 3) {
        //std::cout << ALPHABET_ART[i] << std::endl;
        zicolor color;
        switch(ALPHABET_ART[i]) {
            case '+':
            case '-':
            case '|':
                color.r = 255;
                color.g = 255;
                color.b = 255;
                break;
                
            default:
                color.r = 0;
                color.g = 0;
                color.b = 0;
                break;
        }
        m_texture.push_back(color);
    }
    set_texture_ready(false);
     */
}
