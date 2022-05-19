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
    QVector<qint16> input = {0, 1, 2, 3};
    QVector<Card> output = RollDices::Private::translateNumbers(input);
    Card()
}
