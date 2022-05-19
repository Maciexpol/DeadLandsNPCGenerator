#ifndef ROLLDICES_H
#define ROLLDICES_H

#include <QVector>
#include <QtAlgorithms>
#include <algorithm>
#include <random>
#include "card.h"
#include "dice.h"

namespace RollDices {

    bool compareCards(Card a, Card b);

    QVector<Dice> translateCards(QVector<Card> deck);
    QVector<Dice> generateDices();
    QVector<qint16> generateBasicDeck();

    namespace Private{
        QVector<Card> translateNumbers(QVector<qint16> numbers);
        QVector<Card> rollCards();
        QVector<Card> selectCards(QVector<Card> deck);
    }
}

#endif // ROLLDICES_H
