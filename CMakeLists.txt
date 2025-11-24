cmake_minimum_required(VERSION 3.10)
project(TestAndroidApp)

# --- ANDROID SETUP ---
if(ANDROID)
    # 1. Locate the NDK's Native App Glue source code
    set(APP_GLUE_DIR "${ANDROID_NDK}/sources/android/native_app_glue")
    
    # 2. Create a static library for the Glue code
    add_library(app-glue STATIC "${APP_GLUE_DIR}/android_native_app_glue.c")
    target_include_directories(app-glue PUBLIC ${APP_GLUE_DIR})

    # 3. Create YOUR shared library
    # Note: The library name MUST match what we put in AndroidManifest.xml later
    add_library(test_android_app SHARED src/main.cpp)

    # 4. Link libraries
    # 'android' -> Native window management
    # 'log'     -> Logcat support
    # 'app-glue'-> The library we just created above
    target_link_libraries(
       test_android_app 
       app-glue 
       android 
       log
       "-u ANativeActivity_onCreate" 
    )

# --- WINDOWS SETUP ---
else()
    # Standard executable for Desktop
    add_executable(test_android_app src/main.cpp)
endif()