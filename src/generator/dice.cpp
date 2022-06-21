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

QString Dice::toQstring() const{
    QString output = QString::number(number) + QString("d") + QString::number(sides);
    std::cout << "The dice: " << output.toStdString() << " --- expected: " << number << "d" << sides<< std::endl;
    return output;
}

bool Dice::operator < (Dice a){
    if( a.getSides() > sides)
        return true;
    else if(a.getNumber() > number and a.getSides() == sides)
        return true;
    else
        return false;
}

bool Dice::operator > (Dice a){
    if( a.getSides() < sides )
        return true;
    else if(a.getNumber() < number and a.getSides() == sides)
        return true;
    else
        return false;
}

bool Dice::operator <= (Dice a){
    if( a.getSides() > sides)
        return true;
    else if(a.getNumber() >= number and a.getSides() == sides)
        return true;
    else
        return false;
}

bool Dice::operator >= (Dice a){
    if( a.getSides() < sides)
        return true;
    else if(a.getNumber() <= number and a.getSides() == sides)
        return true;
    else
        return false;
}

QDomElement Dice::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("dice");

    element.setAttribute("number", this->number);
    element.setAttribute("sides", this->sides);
    return element;
}

void Dice::XmlDeserialize(const QDomElement &element) {
    this->number = static_cast<qint16>(element.attribute("number", "0").toInt());
    this->sides = static_cast<qint16>(element.attribute("sides", "0").toInt());
}
