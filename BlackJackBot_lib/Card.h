#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    enum Suit {
        SPADES,
        HEARTS,
        DIAMONDS,
        CLUBS
    };

    enum Value {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13
    };

    Card(Suit suit, Value value);
    ~Card();

    //Returns the suit and value of the card as a string
    std::string toString() const;

    //Handle blackjack logic of getting a cards in game value
    int getCardValue() const;


private:
    Suit suit;
    Value value;

    //Easily convert the enums to strings
    const static std::string SUIT_STRINGS[];
    const static std::string VALUE_STRINGS[];
};

#endif // CARD_H
