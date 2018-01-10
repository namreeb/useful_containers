# Test program for cyclic container
add_executable(cyclic_test cyclic_test.cpp "${CMAKE_CURRENT_SOURCE_DIR}/../include/cyclic.hpp")

target_include_directories(cyclic_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# Test program for priority container 
add_executable(priority priority_test.cpp "${CMAKE_CURRENT_SOURCE_DIR}/../include/priority.hpp")

target_include_directories(priority PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include/")