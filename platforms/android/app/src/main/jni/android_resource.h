#pragma once

#include <platform/iresource.h>

class android_app;

class android_resource : public iresource
{
public:
    android_resource(android_app* app);
    ~android_resource() override;

    std::string get_text_resource(const std::string& name) const override;

    void save_text_data(const std::string& name, const std::string& data) override;
    std::string load_text_data(const std::string& name) const override;

private:
    android_app* m_app;
};
