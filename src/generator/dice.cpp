#include "dice.h"
#include <random>
Dice::Dice(Card card)
{
    if(card.getFace() == 2)
        dice = 4;
    else if(card.getFace() <= 8)
        dice = 6;
    else if(card.getFace() <= 11)
        dice = 8;
    else if(card.getFace() <= 13)
        dice = 10;
    else if(card.getFace() == 14)
        dice = 12;

    SUITS suit = card.getSuit();

    if(card.getSuit() == SUITS::joker){
        dice = 12;
        std::default_random_engine generator;
        std::uniform_int_distribution<qint16> distribution(0,51);
        qint16 rolled = distribution(generator);
        suit = Card(rolled).getSuit();
    }

    number = suit + 1;
}

QDomElement Dice::XmlSerialize(QDomDocument &doc) const {
    QDomElement element = doc.createElement("dice");
    element.setAttribute("number", this->number);
    element.setAttribute("dice", this->dice);
    return element;
}

void Dice::XmlDeserialize(const QDomElement &element) {

}
