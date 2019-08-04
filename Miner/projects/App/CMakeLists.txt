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
    #miner.cpp
    ${GLOBAL_INCLUDE_PATH}/mainwindow.h
    ${GLOBAL_INCLUDE_PATH}/GraphicScene/graphiccell.h
    ${GLOBAL_INCLUDE_PATH}/Core/cell.h
    ${GLOBAL_INCLUDE_PATH}/Draw/icellpainter.h
    ${GLOBAL_INCLUDE_PATH}/Draw/cellpainter.h
    ${GLOBAL_INCLUDE_PATH}/Core/minefield.h
    ${GLOBAL_INCLUDE_PATH}/GraphicScene/minescene.h
    ${GLOBAL_INCLUDE_PATH}/Core/minercore.h
    #${GLOBAL_INCLUDE_PATH}/miner.h
    ${GLOBAL_INCLUDE_PATH}/Core/icell.h
    ${GLOBAL_INCLUDE_PATH}/Global/core_global.h
    ${GLOBAL_INCLUDE_PATH}/Global/graphic_scene_global.h
    ${GLOBAL_INCLUDE_PATH}/Global/draw_global.h
    ${GLOBAL_INCLUDE_PATH}/logger.h
)


target_link_libraries(miner Qt5::Widgets Core GraphicScene DrawPlugin)

