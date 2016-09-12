#include <algorithm>

#include "zwidget_builder.h"

void zwidget_builder::generate_text_geom(const std::string& text, float width, float height, std::vector<zvec2>& buffer)
{
    const size_t size(text.size() * 6);
    buffer.resize(0);
    buffer.reserve(size);

    float w1 = +1.0f * width / text.size();
    float offset_x = -1.0 / 2 * width + 1.0 / 2 * w1;

    std::vector<zvec2> temp;
    for(size_t i = 0; i < text.size(); i++) {
        const zvec2 offset{ offset_x + w1 * i, 0 };
        generate_symbol_geom(w1, height, temp);
        std::for_each(temp.begin(), temp.end(), [&buffer, &offset](const zvec2& vec){
            buffer.push_back(vec + offset);
        });
    }
}

void zwidget_builder::generate_text_coord(const std::string& text, std::vector<zvec2>& buffer)
{
    const size_t size(text.size() * 6);
    buffer.resize(0);
    buffer.reserve(size);

    std::vector<zvec2> temp;
    for(size_t i = 0; i < text.size(); i++) {
        generate_symbol_coord(text[i], temp);
        buffer.insert(buffer.end(), temp.begin(), temp.end());
    }
}

void zwidget_builder::generate_symbol_geom(float width, float height, std::vector<zvec2>& buffer)
{
    buffer.resize(0);
    buffer.reserve(6);

    buffer.push_back(zvec2{-0.5f * width, +0.5f * height});
    buffer.push_back(zvec2{-0.5f * width, -0.5f * height});
    buffer.push_back(zvec2{+0.5f * width, +0.5f * height});

    buffer.push_back(zvec2{-0.5f * width, -0.5f * height});
    buffer.push_back(zvec2{+0.5f * width, +0.5f * height});
    buffer.push_back(zvec2{+0.5f * width, -0.5f * height});
}

void zwidget_builder::generate_symbol_coord(char symbol, std::vector<zvec2>& buffer)
{
    int sym = symbol;
    int row = sym / 16;
    int pos = sym % 16;

    const float step = 1.0f / 16;

    buffer.resize(0);
    buffer.reserve(6);

    buffer.push_back(zvec2{+0.0f + pos * step,        0.0f + row * step       });
    buffer.push_back(zvec2{+0.0f + pos * step,        1.0f * step + row * step});
    buffer.push_back(zvec2{+1.0f * step + pos * step, 0.0f + row * step       });

    buffer.push_back(zvec2{+0.0f + pos * step,        1.0f * step + row * step});
    buffer.push_back(zvec2{+1.0f * step + pos * step, 0.0f + row * step       });
    buffer.push_back(zvec2{+1.0f * step + pos * step, 1.0f * step + row * step});
}
