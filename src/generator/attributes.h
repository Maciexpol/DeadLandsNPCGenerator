#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include <random>
#include "dices.h"
#include "attribute.h"
#include "src/serializable.h"
#include "src/memio.h"

/*!
 * \brief Contains all attributes, rolls distribution of ability lvl points between attributes
 */
class Attributes : Serializable
{
private:
    // Remember to serialize newly added objects in XmlSerialize
    QVector<Attribute> attributes;

public:
    Attributes() {};
    Attributes(const qint16 & characterLvlPoints, const Dices & dices);
    Attributes(const Dices & dices);

    Attribute getAttribute(ATTRIBUTES sName) const;

    /*!
     * \brief distribute lvl points between attributes
     * \param points
     */
    void rollAttributesLvlPoints(const qint16 & characterLvlPoints);

    /*!
     * \brief zeoros abilities lvl and abilitiesLvlSum in all attributes
     */
    void clearAttributesLvlPoints();

    qint16 generateLvlPoints();

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTES_H
