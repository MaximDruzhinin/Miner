cmake_minimum_required(VERSION 3.0.0)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

link_directories(${LIBRARY_OUTPUT_PATH})

add_definitions(-DGRAPHICSCENE_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

file(GLOB SOURCE
    graphic_cell.cpp
    mine_scene.cpp
    factory.cpp
    miner.cpp
    ${GLOBAL_INCLUDE_PATH}/gui/graphic_cell.h
    ${GLOBAL_INCLUDE_PATH}/gui/mine_scene.h
    ${GLOBAL_INCLUDE_PATH}/core/cell.h
    ${GLOBAL_INCLUDE_PATH}/core/minefield.h
    ${GLOBAL_INCLUDE_PATH}/core/game.h
    ${GLOBAL_INCLUDE_PATH}/gui/factory.h
    ${GLOBAL_INCLUDE_PATH}/gui/miner.h
    ${GLOBAL_INCLUDE_PATH}/gui/logger.h
    ${GLOBAL_INCLUDE_PATH}/global/gui_global.h
    ${GLOBAL_INCLUDE_PATH}/draw/ipainter.h
    )

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets core draw)

add_dependencies(${PROJECT_NAME} core draw)
