#ifndef DICE_H
#define DICE_H
#include "card.h"
#include "/src/serializable.h"

#include <QString>

class Dice : Serializable
{
private:
    qint16 number;
    qint16 dice;

public:

    qint16 getNumber() const{return this->number;}
    qint16 getDice() const{return this->dice;}

    Dice();
    // TODO:
    //  Create creator from card
    Dice(Card card);

    bool operator == (Dice a)
        {return number == a.getNumber() and dice == a.getDice();}

    bool operator < (Dice a)
        {return number < a.getNumber() and dice <= a.getDice();}

    bool operator > (Dice a)
        {return number > a.getNumber() and dice >= a.getDice();}

    bool operator <= (Dice a)
        {return number <= a.getNumber() and dice <= a.getDice();}

    bool operator >= (Dice a)
        {return number >= a.getNumber() and dice >= a.getDice();}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // DICE_H
