cmake_minimum_required(VERSION 3.0.0)

project(draw VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
add_definitions(-DDRAW_LIBRARY -D_CRT_SECURE_NO_WARNINGS)

file(GLOB SOURCE
    painter.cpp
    ${GLOBAL_INCLUDE_PATH}/draw/painter.h
    ${GLOBAL_INCLUDE_PATH}/draw/ipainter.h
    )

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)
