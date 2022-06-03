#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include "attribute.h"
#include "src/serializable.h"

/*!
 * \brief The Attributes class
 * \brief Contains all attributes, rolls distribution of ability lvl points between attributes
 */
class Attributes : Serializable
{
private:
    // Remember to serialize newly added objects in XmlSerialize
    QVector<Attribute> attributes;
public:
    Attributes();

    QVector<Attribute> getAttributes() const{return this->attributes;}

    qint16 calculatePoints();

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTES_H
