#include "rolldices.h"
#include "dice.h"
#include "card.h"
#include <QVector>
#include <QtAlgorithms>

QVector<qint16> RollDices::generateBasicDeck(){
    QVector<qint16> numbers{};
    // add 54 numbers into "deck"
    for(qint16 i = 0; i < 54; i++){
        numbers.push_back(i);
    }

    return numbers;
}

QVector<Card> RollDices::Private::translateNumbers(QVector<qint16> numbers){
    QVector<Card> output{};
    // add translated number for card into output
    for(auto number : numbers){
        output.push_back(Card(number));
    }

    return output;
}

QVector<Card> RollDices::Private::rollCards(){
    // TODO:
    //  Check if it returns exactly 12 cards

    // generate "deck" - numbers
    QVector<qint16> numbers = RollDices::generateBasicDeck();

    // shuffle the deck
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(numbers), std::end(numbers), rng);

    // translate numbers and make real deck
    QVector<Card> deck = RollDices::Private::translateNumbers(numbers);

    // create output container
    QVector<Card> cards;

    // choose first 12 cards
    for(auto card : deck){
        if(cards.size() >= 12)
            break;
        cards.push_back(card);
    }

    return cards;
}

void RollDices::Private::sortCards(QVector<Card> & deck){
     std::sort(deck.begin(), deck.end());
}

QVector<Card> RollDices::Private::selectCards(QVector<Card> deck){
     // TODO:
     //  Problem - at the beggining - unskipable 2's,
     //            need to take cards from the end
     //  -- Check if it works --
     QVector<Card> finalCards;

     RollDices::Private::sortCards(finalCards);

     // adding 2's
     qint16 i = 0;
     while(deck[i].getFace() == FACES::two){
         finalCards.push_back(deck[i]);
         i++;
     }

     // adding rest the best dices
     i = deck.size() - 1;
     while(finalCards.size() < 10){
         finalCards.push_back(deck[i]);
         i--;
     }

     return finalCards;
}

QVector<Dice> RollDices::translateCards(QVector<Card> deck){
    QVector<Dice> dices{};

    // translating cards to dices
    for(auto card : deck){
        dices.push_back(Dice(card));
    }

    return dices;
}

QVector<Dice> RollDices::generateDices(){
    QVector<Card> cards = RollDices::Private::rollCards();
    cards = RollDices::Private::selectCards(cards);
    QVector<Dice> dices = RollDices::translateCards(cards);
    return dices;
}


