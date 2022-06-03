#include "dices.h"

Dices::Dices()
{
    Dices::rollDices();
}

void Dices::rollDices(){
    dices = RollDices::generateDices();
    Dices::sortDices();
}

void Dices::sortDices() {
//    RollDices::Private::sortCards(dices);
}
