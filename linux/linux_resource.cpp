#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "linux_resource.h"
#include "generated_resource.h"

namespace {

bool file_exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

}

linux_resource::linux_resource()
{
    m_folders.push_back("data");
    m_folders.push_back("music");
    m_folders.push_back("shader");
}

linux_resource::~linux_resource()
{
}

std::string linux_resource::get_text_resource(const std::string& name) const
{
    for(size_t i = 0; i < m_folders.size(); i++) {
        std::stringstream sstream;
        sstream << ABS_RES_PATH << "/" << m_folders[i] << "/" << name;

        const std::string filepath(sstream.str());
        if(!file_exists(filepath)) {
            continue;
        }
        std::ifstream t(filepath);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        return str;
    }
    return "";
}
