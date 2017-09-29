#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <streambuf>


#include "qt5_resource.h"
#include "generated_resource.h"

qt5_resource::~qt5_resource()
{
}

std::string qt5_resource::get_text_resource(const std::string& name) const
{
    std::stringstream sstream;
    sstream << ABS_RES_PATH << "/" << name;

    const std::string filepath(sstream.str());

    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

void qt5_resource::save_text_data(const std::string& name, const std::string& data)
{
}

std::string qt5_resource::load_text_data(const std::string& name) const
{
    return "";
}
