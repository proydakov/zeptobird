file(GLOB_RECURSE SHARED_SRC
    "*.h"
    "*.cpp"
    "*.glsl"
    "*.mp3"
    "*.txt"
)

add_library(shared STATIC ${SHARED_SRC})
target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

foreach(loop_var ${SHARED_SRC})

get_filename_component(filepath ${loop_var} DIRECTORY)
string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" localpath ${filepath})
string(REPLACE "${PROJECT_SOURCE_DIR}/" "" localpath ${localpath})
string(REPLACE "/" "\\" localpath ${localpath})
source_group(${localpath} FILES ${loop_var})

endforeach()
