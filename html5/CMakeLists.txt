include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${EMSCRIPTEN_ROOT_PATH}/system/include)

add_library(html5_context STATIC
    sdl_ctx.h
    sdl_ctx.cpp
)

add_executable(zeptobird
    html5_resource.h
    html5_resource.cpp
    html5_sound.h
    html5_sound.cpp
    main.cpp
)

set_target_properties(zeptobird PROPERTIES LINK_FLAGS "-s FULL_ES2=1 --embed-file ${PROJECT_SOURCE_DIR}/shared/resources/shader/model_vertex.glsl@shader/model_vertex.glsl --preload-file ${PROJECT_SOURCE_DIR}/shared/resources/shader/model_fragment.glsl@shader/model_fragment.glsl --preload-file ${PROJECT_SOURCE_DIR}/shared/resources/shader/widget_vertex.glsl@shader/widget_vertex.glsl --preload-file ${PROJECT_SOURCE_DIR}/shared/resources/shader/widget_fragment.glsl@shader/widget_fragment.glsl --preload-file ${PROJECT_SOURCE_DIR}/shared/resources/data/alphabet.txt@data/alphabet.txt")

add_dependencies(zeptobird html5_context)

target_link_libraries(zeptobird shared)
target_link_libraries(zeptobird html5_context)
