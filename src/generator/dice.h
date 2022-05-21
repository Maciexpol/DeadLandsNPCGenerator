#ifndef DICE_H
#define DICE_H
#include "card.h"

#include <QString>

class Dice
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
};

#endif // DICE_H
