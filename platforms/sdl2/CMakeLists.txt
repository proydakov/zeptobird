set(ABS_RES_PATH ${PROJECT_SOURCE_DIR}/shared/resources)

set(FROM_PATH ${PROJECT_SOURCE_DIR}/cmake/resource.h)
set(TO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/generated_resource.h)

configure_file(${FROM_PATH} ${TO_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
if(NOT APPLE)
    find_library(GLESv2_LIBRARY GLESv2)
else()
    find_package(OpenGL REQUIRED)
endif()

add_library(sdl2_platform
    sdl2_application.h
    sdl2_application.cpp
    sdl2_resource.h
    sdl2_resource.cpp
    sdl2_sound.h
    sdl2_sound.cpp
    fake_sound.h
    fake_sound.cpp
    generated_resource.h
)

target_include_directories(sdl2_platform PUBLIC ${SDL2_INCLUDE_DIR})

target_link_libraries(sdl2_platform PUBLIC shared ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY})
if(NOT APPLE)
    target_link_libraries(sdl2_platform PUBLIC ${GLESv2_LIBRARY})
else()
    target_link_libraries(sdl2_platform PUBLIC ${OPENGL_LIBRARIES})
endif()

add_executable(zeptobird
    game_main.cpp
)

target_link_libraries(zeptobird sdl2_platform)
