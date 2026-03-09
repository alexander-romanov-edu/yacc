cmake_minimum_required(VERSION 3.20)

project(06_05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.87 REQUIRED COMPONENTS filesystem)

foreach(lib shared1 shared2)
    add_library(${lib} SHARED 06_05_${lib}.cpp)
    target_include_directories(${lib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_executable(${PROJECT_NAME} 06_05_main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem)
