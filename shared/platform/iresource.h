#pragma once

#include <string>

class iresource
{
public:
    virtual ~iresource();

    virtual std::string get_text_resource(const std::string& name) const = 0;
    virtual void save_text_data(const std::string& name, const std::string& data) = 0;
    virtual std::string load_text_data(const std::string& name) const = 0;
};
