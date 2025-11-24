#include "asset_loader.h"

#if defined(__ANDROID__)
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#else
#include <iostream>
#include <fstream>
#endif

asset_loader::asset_loader(asset_loader_state* state) : m_state(state) {}
asset_loader::~asset_loader() {}

asset_file_data asset_loader::load(const std::string& filename) {
    asset_file_data result;
    result.success = false;
    result.content.clear();

    // --- ANDROID IMPLEMENTATION ---
#if defined(__ANDROID__)
    if (!this->m_state) return result;

    // Get the Asset Manager from the native app glue
    AAssetManager* assetManager = this->m_state->android_state->activity->assetManager;

    // Open the file (relative to the 'assets' folder)
    AAsset* asset = AAssetManager_open(assetManager, filename.c_str(), AASSET_MODE_BUFFER);
    if (!asset) return result;

    // Get size and resize buffer
    off_t length = AAsset_getLength(asset);
    result.content.resize(length);

    // Read data
    AAsset_read(asset, result.content.data(), length);
    AAsset_close(asset);

    result.success = true;

    // --- WINDOWS / DESKTOP IMPLEMENTATION ---
#else
    std::string path = "assets/" + filename;
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    // Get size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read data
    result.content.resize(size);
    if (file.read(reinterpret_cast<char*>(result.content.data()), size)) {
        result.success = true;
    }
#endif

    return result;
}