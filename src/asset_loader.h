#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

#if defined(__ANDROID__)
#include <android_native_app_glue.h>
#endif

struct asset_file_data {
    std::vector<uint8_t> content;
    bool success;
};

struct asset_loader_state {
#if defined(__ANDROID__)
    struct android_app* android_state;
#endif
};

// =========================================================
// CROSS-PLATFORM ASSET LOADER
// =========================================================
struct asset_loader {
    asset_loader(asset_loader_state* state);
    ~asset_loader();

    asset_file_data load(const std::string& filename);

private:
    asset_loader_state* m_state;
};