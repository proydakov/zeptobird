#include <vector>
#include <iostream>
#include <android/asset_manager.h>

#include "android_resource.h"

android_resource::android_resource(AAssetManager* manager) :
    m_manager(manager)
{
}

android_resource::~android_resource()
{
}

std::string android_resource::get_text_resource(const std::string& name) const
{
    AAsset* asset = AAssetManager_open(m_manager, name.c_str(), AASSET_MODE_UNKNOWN);
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
