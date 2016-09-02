add_executable(demo_phys demo_phys.cpp)
target_link_libraries(demo_phys math)
target_link_libraries(demo_phys phys)

add_dependencies(demo_phys math)
add_dependencies(demo_phys phys)
