#include "rolldicestest.h"

RollDicesTest::RollDicesTest(QObject *parent)
    : QObject{parent}
{

}

void RollDicesTest::basicDeckSize(){
    QVector<qint16> deck = RollDices::generateBasicDeck();
    QVERIFY(deck.size() == 54);
}

void RollDicesTest::numbersTranslation(){
    QVector<qint16> input = {0, 12, 13, 52};
    QVector<Card> output = RollDices::Private::translateNumbers(input);
    QVERIFY(output[0].getFace() == FACES::two and output[0].getSuit() == SUITS::clubs);
    QVERIFY(output[1].getFace() == FACES::ace and output[1].getSuit() == SUITS::clubs);
    QVERIFY(output[2].getFace() == FACES::two and output[2].getSuit() == SUITS::diamonds);
    QVERIFY(output[3].getFace() == FACES::two and output[3].getSuit() == SUITS::joker);
}

void sortingCards(){
    QVector<Card> goodDeck = RollDices::Private::translateNumbers(RollDices::generateBasicDeck());

    QVector<Card> toSortDeck = RollDices::Private::translateNumbers(RollDices::generateBasicDeck());

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(toSortDeck), std::end(toSortDeck), rng);

    RollDices::Private::sortCards(toSortDeck);

    for(int i = 0; i < 54; i++){
        QVERIFY(goodDeck[i] == toSortDeck[i]);
    }

}
