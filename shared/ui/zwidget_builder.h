#pragma once

#include <string>
#include <vector>
#include <math/zmath.h>

class zwidget_builder
{
public:
    static void generate_text_geom(const std::string& text, float width, float height, std::vector<zvec2>& buffer);
    static void generate_text_coord(const std::string& text, std::vector<zvec2>& buffer);

    static void generate_symbol_geom (float width, float height, std::vector<zvec2>& buffer);
    static void generate_symbol_coord(char symbol, std::vector<zvec2>& buffer);
};
