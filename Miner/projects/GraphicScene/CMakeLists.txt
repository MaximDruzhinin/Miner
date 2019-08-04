cmake_minimum_required(VERSION 3.0.0)

project(GraphicScene VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

link_directories(${LIBRARY_OUTPUT_PATH})

add_definitions(-DGRAPHICSCENE_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

file(GLOB SOURCE
    graphiccell.cpp
    minescene.cpp
    factory.cpp
    #cellpainter.cpp
    #miner.cpp
    ${GLOBAL_INCLUDE_PATH}/GraphicScene/graphiccell.h
    ${GLOBAL_INCLUDE_PATH}/Global/graphic_scene_global.h
    ${GLOBAL_INCLUDE_PATH}/GraphicScene/minescene.h
    ${GLOBAL_INCLUDE_PATH}/Draw/icellpainter.h
    ${GLOBAL_INCLUDE_PATH}/Core/cell.h
    ${GLOBAL_INCLUDE_PATH}/Core/minefield.h
    ${GLOBAL_INCLUDE_PATH}/GraphicScene/factory.h
    )

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets Core DrawPlugin)


add_dependencies(${PROJECT_NAME} Core DrawPlugin)
