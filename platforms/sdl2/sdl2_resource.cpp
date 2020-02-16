#include <string>
#include <fstream>

#include "sdl2_resource.h"
#include "generated_resource.h"

sdl2_resource::~sdl2_resource()
{
}

std::string sdl2_resource::get_text_resource(const std::string& name) const
{
    std::string filepath;
    filepath.reserve(std::size(ABS_RES_PATH) + 1 + name.size());
    filepath.append(ABS_RES_PATH);
    filepath.append("/");
    filepath.append(name);

    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}

void sdl2_resource::save_text_data(const std::string& key, const std::string& val)
{
    std::ofstream stream(key);
    stream << val;
}

std::string sdl2_resource::load_text_data(const std::string& key) const
{
    std::ifstream t(key);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}
