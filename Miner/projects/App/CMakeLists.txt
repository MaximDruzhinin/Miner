cmake_minimum_required(VERSION 3.1.0)

project(App)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(miner
    mainwindow.ui
    main.cpp
    mainwindow.cpp
    ${GLOBAL_INCLUDE_PATH}/mainwindow.h
    ${GLOBAL_INCLUDE_PATH}/draw/painter.h
    ${GLOBAL_INCLUDE_PATH}/core/cell.h
    ${GLOBAL_INCLUDE_PATH}/core/minefield.h
    ${GLOBAL_INCLUDE_PATH}/core/game.h
    ${GLOBAL_INCLUDE_PATH}/gui/graphic_cell.h
    ${GLOBAL_INCLUDE_PATH}/gui/mine_scene.h
    ${GLOBAL_INCLUDE_PATH}/gui/miner.h
)

target_link_libraries(miner Qt5::Widgets core gui draw)

