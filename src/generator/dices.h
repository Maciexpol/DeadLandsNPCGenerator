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

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;

};

#endif // DICES_H
