cmake_minimum_required(VERSION 3.26)
project(BasicStrategySolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(BasicStrategySolver main.cpp
        BlackJackBot_lib/StrategyGuideHandler.cpp
        BlackJackBot_lib/StrategyGuideHandler.h
        BlackJackBot_lib/Card.cpp
        BlackJackBot_lib/Card.h
        BlackJackBot_lib/Shoe.cpp
        BlackJackBot_lib/Shoe.h
        BlackJackBot_lib/Hand.cpp
        BlackJackBot_lib/Hand.h
        BlackJackBot_lib/DealerHand.cpp
        BlackJackBot_lib/DealerHand.h
        BlackJackBot_lib/PlayerHand.cpp
        BlackJackBot_lib/PlayerHand.h
        BlackJackBot_lib/Table.cpp
        BlackJackBot_lib/Table.h
        BlackJackBot_lib/PlayerBot.cpp
        BlackJackBot_lib/PlayerBot.h
        BlackJackBot_lib/HouseRules.h
        )
