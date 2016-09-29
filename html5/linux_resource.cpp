#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "linux_resource.h"

linux_resource::~linux_resource()
{
}

std::string linux_resource::get_text_resource(const std::string& name) const
{
    std::stringstream sstream;
    sstream << "/" << name;

    const std::string filepath(sstream.str());

    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}

void linux_resource::save_text_data(const std::string& name, const std::string& data)
{
}

std::string linux_resource::load_text_data(const std::string& name) const
{
    return "";
}
