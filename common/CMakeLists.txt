cmake_minimum_required(VERSION 3.10)

include_directories(.)

# Number generator
add_library(number_generator STATIC src/number_generator.cpp )
target_include_directories(number_generator PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

add_executable(random_test tests/test_random.cpp)
target_link_libraries(random_test PRIVATE gtest_main number_generator)
add_test(
        NAME random_test
        COMMAND random_test
)

# Logger
add_library(logger STATIC src/logger.cpp )
target_include_directories(logger PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

