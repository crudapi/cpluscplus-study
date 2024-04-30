cmake_minimum_required(VERSION 3.14)

project(5_4_1_QTimer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(5_4_1_QTimer
  main.cpp
)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
