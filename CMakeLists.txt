cmake_minimum_required(VERSION 3.16)
project(mergerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

add_executable(mergerApp
    src/main.cpp
    src/ui/MainWindow.cpp
    src/core/MergeService.cpp
)

target_include_directories(mergerApp PRIVATE
    src
    src/ui
    src/core
)

target_link_libraries(mergerApp PRIVATE
    Qt5::Widgets
    Qt5::Core
)
