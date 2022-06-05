#ifndef DICES_H
#define DICES_H

#include <QVector>
#include "rolldices.h"
#include "src/serializable.h"

class Dices : Serializable
{
private:
    QVector<Dice> dices;

    void sortDices();

public:
    Dices();

    void rollDices();

    QVector<Dice> getDices() const {return dices;};
    Dice getDice(qint16 index) const {return dices[index];};

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;

};

#endif // DICES_H
