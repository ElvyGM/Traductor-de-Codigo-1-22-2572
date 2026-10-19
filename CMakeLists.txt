cmake_minimum_required(VERSION 3.16)
project(TraductorPythonCSharp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_add_executable(TraductorPythonCSharp WIN32
    main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
    translator.cpp translator.h)
target_link_libraries(TraductorPythonCSharp PRIVATE Qt6::Widgets)
