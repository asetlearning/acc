cmake_minimum_required(VERSION 3.10)

include_directories(.)

add_library(elt STATIC src/word.cpp )

target_include_directories(elt PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(elt PUBLIC number_generator logger)

add_executable(elt_test tests/test_elt.cpp)
target_link_libraries(elt_test PRIVATE gtest_main elt)
add_test(
        NAME elt_test
        COMMAND elt_test
)