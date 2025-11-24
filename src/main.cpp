#include <iostream>
#include <string>

#include "asset_loader.h"

// ============================================================================
// PLATFORM: ANDROID
// ============================================================================
#if defined(__ANDROID__)
#include <android_native_app_glue.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NativeApp", __VA_ARGS__))

// Handle Android Lifecycle events (Focus, Window creation, etc.)
static void handle_cmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
    case APP_CMD_INIT_WINDOW:
        LOGI("Window is ready - you can start rendering now.");
        // In a real game, you would initialize OpenGL/Vulkan here
        break;
    case APP_CMD_TERM_WINDOW:
        LOGI("Window is being destroyed.");
        break;
    }
}

// --- ANDROID ENTRY POINT ---
void android_main(struct android_app* state) {
    LOGI("Entering android_main");

    // Set up the event handler
    state->onAppCmd = handle_cmd;

    asset_loader_state loader_state;
    loader_state.android_state = state;

    asset_loader* loader = new asset_loader(&loader_state);
    asset_file_data result = loader->load("print.txt");
    if (result.success) {
        char* buffer = new char[result.content.size() + 1];
        memcpy(buffer, result.content.data(), result.content.size());
        buffer[result.content.size()] = '\0';
        LOGI("Loaded asset content: %s", buffer);
        delete[] buffer;
    }
    else {
        LOGI("Failed to load asset.");
    }

    // The Main Loop
    while (true) {
        int events;
        struct android_poll_source* source;

        // Poll all events. If timeout is -1, it blocks until an event happens.
        // If timeout is 0, it creates a non-blocking loop (good for games).
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0) {
            if (source != nullptr) {
                source->process(state, source);
            }
            // Check if Android wants us to exit
            if (state->destroyRequested != 0) {
                return;
            }
        }

        // --- GAME LOOP HERE ---
        // Render frames, update logic, etc.
    }
    delete loader;
}

// ============================================================================
// PLATFORM: WINDOWS / DESKTOP
// ============================================================================
#else

// --- WINDOWS ENTRY POINT ---
int main() {
    std::cout << "Booting on Windows Desktop..." << std::endl;

    asset_loader_state loader_state;

    asset_loader* loader = new asset_loader(&loader_state);
    asset_file_data result = loader->load("print.txt");
    if (result.success) {
        char* buffer = new char[result.content.size() + 1];
        memcpy(buffer, result.content.data(), result.content.size());
        buffer[result.content.size()] = '\0';
        std::cout << "Loaded asset content: " << buffer << "\n";
        delete[] buffer;
    }
    else {
        std::cout << "Failed to load asset." << "\n";
    }

    std::cout << "App running. Press Enter to exit." << std::endl;

    std::cin.get();

    delete loader;

    return 0;
}

#endif