cmake_minimum_required(VERSION 3.10)

include_directories(.)

add_library(ac_transformations STATIC src/ac_transformations.cpp )

target_include_directories(ac_transformations PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(ac_transformations PUBLIC elt alphabet number_generator logger)

add_executable(test_ac_transformations tests/test_ac_transformations.cpp)
target_link_libraries(test_ac_transformations PRIVATE gtest_main ac_transformations)
add_test(
        NAME test_ac_transformations
        COMMAND test_ac_transformations
)