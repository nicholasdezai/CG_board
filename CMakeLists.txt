cmake_minimum_required(VERSION 3.29)
project(CG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        REQUIRED
        Widgets)

include_directories(
        mainwindow/include
        canvas/include
        algorithms/include
)

add_executable(CG
        main.cpp
        mainwindow/src/mainwindow.cpp
        canvas/src/canvas.cpp
        mainwindow/include/mainwindow.h
        canvas/include/canvas.h
        algorithms/include/line_algorithms.h
        algorithms/src/line_algorithms.cpp
        algorithms/include/circle_algorithms.h
        algorithms/src/circle_algorithms.cpp
)

target_link_libraries(CG
        Qt::Core
        Qt::Widgets
)

