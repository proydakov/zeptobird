#pragma once

#include <platform/iresource.h>

struct AAssetManager;

class android_resource : public iresource
{
public:
    android_resource(AAssetManager* manager);
    ~android_resource() override;

    std::string get_text_resource(const std::string& name) const override;

private:
    AAssetManager* m_manager;
};
