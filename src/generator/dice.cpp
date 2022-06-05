#include "dice.h"
#include <random>
Dice::Dice(Card card)
{
    if(card.getFace() == 2)
        sides = 4;
    else if(card.getFace() <= 8)
        sides = 6;
    else if(card.getFace() <= 11)
        sides = 8;
    else if(card.getFace() <= 13)
        sides = 10;
    else if(card.getFace() == 14)
        sides = 12;

    SUITS suit = card.getSuit();

    if(card.getSuit() == SUITS::joker){
        sides = 12;
        std::default_random_engine generator;
        std::uniform_int_distribution<qint16> distribution(0,51);
        qint16 rolled = distribution(generator);
        suit = Card(rolled).getSuit();
    }

    number = suit + 1;
}

QDomElement Dice::XmlSerialize() const {
    QDomElement element;
    element.setTagName("dice");
    element.setAttribute("number", this->number);
    element.setAttribute("sides", this->sides);
    return element;
}

void Dice::XmlDeserialize(const QDomElement &element) {

}
