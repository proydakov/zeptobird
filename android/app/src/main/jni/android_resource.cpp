#include <vector>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

#include "android_resource.h"

#include <android/asset_manager.h>
#include <android_native_app_glue.h>

android_resource::android_resource(android_app* app) :
    m_app(app)
{
}

android_resource::~android_resource()
{
}

std::string android_resource::get_text_resource(const std::string& name) const
{
    AAsset* asset = AAssetManager_open(m_app->activity->assetManager, name.c_str(), AASSET_MODE_UNKNOWN);
    if (NULL == asset) {
        std::cout << "_ASSET_NOT_FOUND_" << std::endl;
        return "";
    }
    long size = AAsset_getLength(asset);
    std::vector<char> buffer;
    buffer.resize(size);

    AAsset_read (asset, buffer.data(), size);
    std::string resource(buffer.begin(), buffer.begin() + size);
    AAsset_close(asset);

    return resource;
}

void android_resource::save_text_data(const std::string& name, const std::string& data)
{
    std::stringstream sstream;
    sstream << m_app->activity->externalDataPath << "/" << name;
    const std::string filepath = sstream.str();

    std::ofstream fstream(filepath);
    fstream << data;
    fstream.close();
}

std::string android_resource::load_text_data(const std::string& name) const
{
    std::stringstream sstream;
    sstream << m_app->activity->externalDataPath << "/" << name;
    const std::string filepath = sstream.str();

    std::ifstream fstream(filepath);
    std::string str((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());
    fstream.close();

    return str;
}
