#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include "attribute.h"

/*!
 * \brief The Attributes class
 * \brief Contains all attributes, rolls distribution of ability lvl points between attributes
 */
class Attributes
{
private:
    QVector<Attribute> attributes;
public:
    Attributes();

    QVector<Attribute> getAttributes() const{return this->attributes;}

    qint16 calculatePoints();
};

#endif // ATTRIBUTES_H
