#include "rolldices.h"
#include "dice.h"
#include "card.h"
#include <QVector>

QVector<Dice> RollDices::generateDices(){
    QVector<Card> cards = RollDices::rollCards();
    cards = RollDices::selectCards(cards);
    return RollDices::translateCards(cards);
}
