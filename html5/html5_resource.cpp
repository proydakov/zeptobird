#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <streambuf>

#include <emscripten.h>

#include "html5_resource.h"

html5_resource::~html5_resource()
{
}

std::string html5_resource::get_text_resource(const std::string& name) const
{
    std::cout << "html5_resource::get_text_resource " << name << std::endl;

    std::stringstream sstream;
    sstream << name;

    const std::string filepath(sstream.str());

    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

void html5_resource::save_text_data(const std::string& name, const std::string& data)
{
    std::cout << "html5_resource::save_text_data " << name << std::endl;

    EM_ASM_ARGS({
        var name_str = Pointer_stringify($0);
        var data_str = Pointer_stringify($1);

        localStorage.setItem(name_str, data_str);
    }, name.c_str(), data.c_str());
}

std::string html5_resource::load_text_data(const std::string& name) const
{
    std::cout << "html5_resource::load_text_data " << name << std::endl;

    EM_ASM_ARGS({
        var name_str = Pointer_stringify($0);

        var buffer = "";
        var item = localStorage.getItem(name_str);
        if(item != null) {
            buffer = item;
        }

        FS.writeFile('buffer', buffer);
    }, name.c_str());

    std::ifstream t("buffer");
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}
