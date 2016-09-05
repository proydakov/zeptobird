#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>


#include "linux_resource.h"
#include "generated_resource.h"

linux_resource::~linux_resource()
{
}

std::string linux_resource::get_text_resource(const std::string& name) const
{
    std::stringstream sstream;
    sstream << ABS_RES_PATH << "/" << name;

    std::ifstream t(sstream.str());
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}
