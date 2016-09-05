add_executable(test_phys test_phys.cpp)
target_link_libraries(test_phys shared)

add_dependencies(test_phys shared)
