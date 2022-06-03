#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include "dices.h"
#include "attribute.h"
#include "src/serializable.h"

/*!
 * \brief Contains all attributes, rolls distribution of ability lvl points between attributes
 */
class Attributes : Serializable
{
private:
    // Remember to serialize newly added objects in XmlSerialize
    QVector<Attribute> attributes;
public:
    Attributes(const qint16 & characterLvlPoints, const Dices & dices);

    Attribute getAttribute(ATTRIBUTES sName) const;
    /*!
     * \brief distribute lvl points between attributes
     * \param points
     */
    void rollAttributesLvlPoints(const qint16 & characterLvlPoints);

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTES_H
