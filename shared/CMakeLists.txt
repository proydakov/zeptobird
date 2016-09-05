file(GLOB_RECURSE SHARED_SRC
    "*.h"
    "*.cpp"
    "*.glsl"
)

add_library(shared STATIC ${SHARED_SRC})
