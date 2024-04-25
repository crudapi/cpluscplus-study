cmake_minimum_required(VERSION 3.3)

#create a project
project(cpp_project)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}) 

#create exe file
add_executable(main-answer main-answer.cpp)

add_executable(main-question main-question.cpp)
