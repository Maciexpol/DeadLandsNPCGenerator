#ifndef DICES_H
#define DICES_H

#include <QVector>
#include "rolldices.h"

class Dices
{
private:
    QVector<Dice> dices;

    void sortDices();

public:
    Dices();

    void rollDices();

};

#endif // DICES_H
