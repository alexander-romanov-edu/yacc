cmake_minimum_required(VERSION 3.20)

project(cpp_course_tasks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TASK_SOURCES
    03_01.cpp
    03_02.cpp
    03_03.cpp
    03_04.cpp
    03_05.cpp
    03_06.cpp
    03_07.cpp
    03_09.cpp
    03_10.cpp
)

foreach(src ${TASK_SOURCES})
    get_filename_component(exe ${src} NAME_WE)
    add_executable(${exe} ${src})
endforeach()

