#ifndef ROLLDICES_H
#define ROLLDICES_H

#include <QVector>
#include <QtAlgorithms>
#include <algorithm>
#include <random>
#include "card.h"
#include "dice.h"

namespace RollDices {
    namespace {

        QVector<qint16> generateBasicDeck(){
            QVector<qint16> numbers{};
            // add 54 numbers into "deck"
            for(qint16 i = 0; i < 54; i++){
                numbers.push_back(i);
            }

            return numbers;
        }

        QVector<Card> translateNumbers(QVector<qint16> numbers){
            QVector<Card> output{};
            // add translated number for card into output
            for(auto number : numbers){
                output.push_back(Card(number));
            }

            return output;
        }

        QVector<Card> rollCards(){
            // generate "deck" - numbers
            QVector<qint16> numbers = generateBasicDeck();

            // shuffle the deck
            auto rng = std::default_random_engine {};
            std::shuffle(std::begin(numbers), std::end(numbers), rng);

            // translate numbers and make real deck
            QVector<Card> deck = translateNumbers(numbers);

            // create output container
            QVector<Card> cards(12);

            // choose first 12 cards
            std::copy(deck.begin(), deck.begin() + 12, cards);

            return cards;
        }


        QVector<Card> selectCards(QVector<Card> deck);

        QVector<Dice> translateCards(QVector<Card> deck);
    }

    QVector<Dice> generateDices();
}

#endif // ROLLDICES_H
