file(GLOB_RECURSE SHARED_SRC
    "*.h"
    "*.cpp"
    "*.glsl"
    "*.mp3"
    "*.txt"
)

add_library(shared STATIC ${SHARED_SRC})
