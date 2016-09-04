#pragma once

#include <string>

class iresource
{
public:
    virtual ~iresource();

    virtual std::string load_text_resource(const std::string& name) const = 0;
};
