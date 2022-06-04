#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QVector>
#include <random>
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
<<<<<<< HEAD
    Attributes(const qint16 & characterLvlPoints, const Dices & dices);
=======
    Attributes() = default;
>>>>>>> 6a45487ee355600950698515099784cd9bcad0a0

    Attribute getAttribute(ATTRIBUTES sName) const;
    /*!
     * \brief distribute lvl points between attributes
     * \param points
     */
    void rollAttributesLvlPoints(const qint16 & characterLvlPoints);

    void clearAttributesLvlPoints();

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTES_H
