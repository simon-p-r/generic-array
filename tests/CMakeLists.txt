# find check 
find_library(CHECK_LIBRARY NAMES check)
find_library(CHECK_COMPAT_LIBRARY NAMES compat)
find_path(CHECK_INCLUDE_DIR check.h)


set(TEST_SOURCES
    test.c
    custom_array.c
)

add_executable(array_tests ${TEST_SOURCES})

target_include_directories(
    array_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CHECK_INCLUDE_DIR}
)

target_link_libraries(
    array_tests 
    PRIVATE
    generic-array
    ${CHECK_LIBRARY}
    ${CHECK_COMPAT_LIBRARY}
)

