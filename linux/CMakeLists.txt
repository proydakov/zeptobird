include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FIND_PACKAGE(SDL2)

FIND_LIBRARY(GLESv2_LIBRARY GLESv2)
FIND_LIBRARY(EGL_LIBRARY    EGL   )
FIND_LIBRARY(M_LIBRARY      m     )
FIND_LIBRARY(X11_LIBRARY    X11   )

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})

add_library(linux_context STATIC
    esUtil.h
    esUtil.c
)

add_executable(zeptobird
    linux_resource.h
    linux_resource.cpp
    linux_sound.h
    linux_sound.cpp
    generated_resource.h
    main.cpp
)

add_dependencies(zeptobird linux_context)

target_link_libraries(zeptobird shared)
target_link_libraries(zeptobird linux_context)
target_link_libraries(zeptobird ${GLESv2_LIBRARY})
target_link_libraries(zeptobird ${EGL_LIBRARY})
target_link_libraries(zeptobird ${M_LIBRARY})
target_link_libraries(zeptobird ${X11_LIBRARY})
target_link_libraries(zeptobird ${SDL2_LIBRARY})
target_link_libraries(zeptobird ${SDL2_MIXER_LIBRARY})
