cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_BUILD_TYPE Release)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# Set common compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fno-rtti -fno-exceptions")

# build native_app_glue as a static lib
add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

set(shared_folder ../../../../../../shared/)
add_subdirectory(${shared_folder} binshared)

# now build app's shared lib
add_library(game SHARED
    android_egl_engine.cpp
    android_egl_engine.h
    android_logger.cpp
    android_logger.h
    android_resource.cpp
    android_resource.h
    android_sound.cpp
    android_sound.h
    android_main.cpp
)

target_include_directories(game PRIVATE SYSTEM
    ${ANDROID_NDK}/sources/android/native_app_glue
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# add lib dependencies
target_link_libraries(game
     shared
     android
     native_app_glue
     atomic
     EGL
     GLESv2
     log
)
