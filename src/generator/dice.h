#ifndef DICE_H
#define DICE_H
#include "card.h"
#include "src/serializable.h"

#include <QString>

class Dice : Serializable
{
private:
    qint16 number;
    qint16 sides;

public:

    qint16 getNumber() const{return this->number;}
    qint16 getSides() const{return this->sides;}

    Dice(){};
    // TODO:
    //  Create creator from card
    Dice(Card card);

    bool operator == (Dice a)
        {return number == a.getNumber() and sides == a.getSides();}

    bool operator < (Dice a)
        {return number < a.getNumber() and sides <= a.getSides();}

    bool operator > (Dice a)
        {return number > a.getNumber() and sides >= a.getSides();}

    bool operator <= (Dice a)
        {return number <= a.getNumber() and sides <= a.getSides();}

    bool operator >= (Dice a)
        {return number >= a.getNumber() and sides >= a.getSides();}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // DICE_H
