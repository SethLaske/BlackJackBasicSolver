project(BlackJackBot_lib)

set(HEADER_FILES
        Card.h
        Shoe.h
        Table.h
        HouseRules.h
        Hand.h
        DealerHand.h
        PlayerHand.h
        PlayerBot.h
        StrategyGuideHandler.h
        StrategyGuideGenerator.cpp
        StrategyGuideGenerator.h
        GeneticAlgorithmManager.cpp
        GeneticAlgorithmManager.h
)

set(SOURCE_FILES
        Card.cpp
        Shoe.cpp
        Table.cpp
        Hand.cpp
        DealerHand.cpp
        PlayerHand.cpp
        PlayerBot.cpp
        StrategyGuideHandler.cpp
        StrategyGuideGenerator.cpp
        StrategyGuideGenerator.h
        GeneticAlgorithmManager.cpp
        GeneticAlgorithmManager.h
        HouseRules.cpp
)

add_library(BlackJackBot_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})