cmake_minimum_required(VERSION 3.16)
project(QtPdfMerge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic moc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtPdfMerge
    src/main.cpp
    src/ui/MainWindow.cpp
    src/core/MergeService.cpp
)

target_include_directories(QtPdfMerge PRIVATE
    src
    src/ui
    src/core
)

target_link_libraries(QtPdfMerge PRIVATE Qt6::Widgets)

