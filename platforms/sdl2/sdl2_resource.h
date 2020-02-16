#pragma once

#include <platform/iresource.h>

class sdl2_resource : public iresource
{
public:
    ~sdl2_resource() override;

    std::string get_text_resource(const std::string& name) const override;
    void save_text_data(const std::string& name, const std::string& data) override;
    std::string load_text_data(const std::string& name) const override;
};
