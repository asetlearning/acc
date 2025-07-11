cmake_minimum_required(VERSION 3.10)

include_directories(.)

add_library(alphabet STATIC src/alphabet.cpp )

target_include_directories(alphabet PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(alphabet PUBLIC elt logger)

add_executable(test_alphabet tests/test_alphabet.cpp)
target_link_libraries(test_alphabet PRIVATE gtest_main alphabet elt)
add_test(
        NAME test_alphabet
        COMMAND test_alphabet
)