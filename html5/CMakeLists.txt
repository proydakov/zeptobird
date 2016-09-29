include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${EMSCRIPTEN_ROOT_PATH}/system/include)

add_library(html5_context STATIC
    esUtil.h
    esUtil.c
)

add_executable(zeptobird
    linux_resource.h
    linux_resource.cpp
    linux_sound.h
    linux_sound.cpp
    main.cpp
)

add_dependencies(zeptobird html5_context)

target_link_libraries(zeptobird shared)
target_link_libraries(zeptobird html5_context)
