cmake_minimum_required(VERSION 3.1.0)

project(miner)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_definitions(-DCORE_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

add_definitions(-DGRAPHICSCENE_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

add_definitions(-DDRAW_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GraphicScene)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DrawPlugin)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/App)

