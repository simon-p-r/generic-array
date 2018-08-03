cmake_minimum_required(VERSION 3.10.0)

project(generic-array)

file(
    GLOB 
    ARRAYS_SRC_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.c
)

add_library(generic-array ${ARRAYS_SRC_FILES})

target_include_directories(
    generic-array
    PRIVATE 
      ${CMAKE_SOURCE_DIR}/include
)


# tests
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)


enable_testing()
add_test(NAME gen_array_tests COMMAND array_tests)



