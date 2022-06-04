#ifndef ROLLDICES_H
#define ROLLDICES_H

#include <QVector>
#include <QtAlgorithms>
#include <algorithm>
#include <random>
#include "card.h"
#include "dice.h"

namespace RollDices {

    namespace Private{
        void sortCards(QVector<Card> & deck);
        QVector<Card> translateNumbers(QVector<qint16> numbers);
        QVector<Card> rollCards();
        QVector<Card> selectCards(QVector<Card> deck);
    }

    QVector<qint16> generateBasicDeck();
    /*!
     * \brief translateCards
     * \param deck
     * \return
     */
    QVector<Dice> translateCards(QVector<Card> deck);

    /*!
     * \brief Rolling Dices using cards
     * \return Vector of 10 rolled Dices
     */
    QVector<Dice> generateDices();

}

#endif // ROLLDICES_H
