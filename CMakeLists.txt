cmake_minimum_required(VERSION 3.26)
project(BasicStrategySolver)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(BasicStrategySolver ${SOURCE_FILES})

include_directories(BlackJackBot_lib)
add_subdirectory(BlackJackBot_lib)

target_link_libraries(BasicStrategySolver BlackJackBot_lib)

