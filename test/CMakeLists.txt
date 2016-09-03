add_executable(test_phys test_phys.cpp)
target_link_libraries(test_phys math)
target_link_libraries(test_phys phys)

add_dependencies(test_phys math)
add_dependencies(test_phys phys)
