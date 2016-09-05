include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FIND_LIBRARY(GLESv2_LIBRARY GLESv2)
FIND_LIBRARY(EGL_LIBRARY    EGL   )
FIND_LIBRARY(M_LIBRARY      m     )
FIND_LIBRARY(X11_LIBRARY    X11   )

add_executable(zeptobird
    esUtil.h
    esUtil.c
    linux_resource.h
    linux_resource.cpp
    generated_resource.h
    zeptobird.cpp
)

target_link_libraries(zeptobird shared)
target_link_libraries(zeptobird ${GLESv2_LIBRARY})
target_link_libraries(zeptobird ${EGL_LIBRARY})
target_link_libraries(zeptobird ${M_LIBRARY})
target_link_libraries(zeptobird ${X11_LIBRARY})
