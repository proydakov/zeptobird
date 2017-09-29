set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/proydakov/sdks/qt5.9.1/5.9.1/gcc_64")

set(ABS_RES_PATH ${PROJECT_SOURCE_DIR}/shared/resources)

set(FROM_PATH ${PROJECT_SOURCE_DIR}/cmake/resource.h)
set(TO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/generated_resource.h)

configure_file(${FROM_PATH} ${TO_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5Core       REQUIRED)
find_package(Qt5Gui        REQUIRED)
find_package(Qt5Widgets    REQUIRED)
find_package(Qt5Multimedia REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS}      )
include_directories(${Qt5Gui_INCLUDE_DIRS}       )
include_directories(${Qt5Widgets_INCLUDE_DIRS}   )
include_directories(${Qt5Multimedia_INCLUDE_DIRS})

FIND_LIBRARY(GLESv2_LIBRARY GLESv2)

add_executable(zeptobird
    qt5_resource.h
    qt5_resource.cpp
    qt5_sound.h
    qt5_sound.cpp
    gles_view.h
    gles_view.cpp
    generated_resource.h
    main.cpp
)

target_link_libraries(zeptobird shared)

target_link_libraries(zeptobird Qt5::Core)
target_link_libraries(zeptobird Qt5::Gui)
target_link_libraries(zeptobird Qt5::Widgets)
target_link_libraries(zeptobird Qt5::Multimedia)
target_link_libraries(zeptobird ${GLESv2_LIBRARY})
