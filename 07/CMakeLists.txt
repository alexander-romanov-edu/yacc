cmake_minimum_required(VERSION 3.20)

project(07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TASK_SOURCES
    07_01.cpp
    07_02_bad_alloc.cpp
    07_02_bad_optional_access.cpp
    07_02_bad_variant_access.cpp
    07_02_length_error.cpp
    07_02_out_of_range.cpp
)

foreach(src ${TASK_SOURCES})
    get_filename_component(exe ${src} NAME_WE)
    add_executable(${exe} ${src})
    target_include_directories(${exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

find_package(GTest REQUIRED)
include(GoogleTest)

enable_testing()

set(TEST_SOURCES
  07_02_test.cpp
)
foreach(src ${TEST_SOURCES})
    get_filename_component(exe ${src} NAME_WE)
    add_executable(${exe} ${src})
    target_include_directories(${exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${exe} PRIVATE GTest::gtest_main)
    gtest_discover_tests(${exe})
endforeach()

