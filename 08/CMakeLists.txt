cmake_minimum_required(VERSION 3.20)

project(08 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TASK_SOURCES
    08_01.cpp
    08_04.cpp
    08_05_timer.cpp
)
find_package(benchmark REQUIRED)
foreach(src ${TASK_SOURCES})
    get_filename_component(exe ${src} NAME_WE)
    add_executable(${exe} ${src})
    target_include_directories(${exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${exe} PRIVATE benchmark::benchmark)
endforeach()

find_package(GTest REQUIRED)
include(GoogleTest)

enable_testing()

set(TEST_SOURCES
  08_02_integers.cpp
  08_03_log.cpp
)
foreach(src ${TEST_SOURCES})
    get_filename_component(exe ${src} NAME_WE)
    add_executable(${exe} ${src})
    target_include_directories(${exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${exe} PRIVATE GTest::gtest_main)
    gtest_discover_tests(${exe})
endforeach()

