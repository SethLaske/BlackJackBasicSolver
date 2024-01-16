cmake_minimum_required(VERSION 3.26)
project(BasicStrategySolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(BasicStrategySolver main.cpp
        StrategyGuideHandler.cpp
        StrategyGuideHandler.h
        Card.cpp
        Card.h
        Shoe.cpp
        Shoe.h)
