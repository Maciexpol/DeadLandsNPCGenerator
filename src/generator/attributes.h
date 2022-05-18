#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include "attribute.h"

class Attributes
{
private:
    QVector<Attribute> attributes;
public:
    Attributes();

    QVector<Attribute> getAttributes() const{return this->attributes;}

    //! Calculates combined points from all attributes
    qint16 calculatePoints();
};

#endif // ATTRIBUTES_H
