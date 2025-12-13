cmake_minimum_required(VERSION 3.16)

project(QT_Mario LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    game.cpp
    game.h
    logindialog.cpp
    logindialog.h
)

add_executable(QT_Mario ${PROJECT_SOURCES})

target_link_libraries(QT_Mario PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
