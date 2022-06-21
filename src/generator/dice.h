#ifndef DICE_H
#define DICE_H
#include "card.h"
#include "src/serializable.h"

#include <QString>
#include <iostream>

class Dice : Serializable
{
private:
    qint16 number;
    qint16 sides;

public:

    qint16 getNumber() const{return this->number;}
    qint16 getSides() const{return this->sides;}
    QString toQstring() const;

    Dice(){};
    // TODO:
    //  Create creator from card
    Dice(Card card);

    friend std::ostream & operator<<(std::ostream & os, const Dice & s)
        { os << std::to_string(s.getNumber()) << "d" << std::to_string(s.getSides()); return os;};

    bool operator == (Dice a)
        {return number == a.getNumber() and sides == a.getSides();}
    bool operator < (Dice a);
    bool operator > (Dice a);
    bool operator <= (Dice a);
    bool operator >= (Dice a);

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // DICE_H
