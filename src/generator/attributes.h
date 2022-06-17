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

    Attribute* getAttribute(const ATTRIBUTES & sName);
    QVector<Attribute> getAttributesVector() const {return attributes;};

    /*!
     * \brief distribute lvl points between attributes
     * \param points
     */
    void rollAttributesLvlPoints(const qint16 & characterLvlPoints);

    /*!
     * \brief zeoros abilities lvl and abilitiesLvlSum in all attributes
     */
    void clearAttributesLvlPoints();

    void clearAttributesLvlSum();

    /*!
     * \brief Counts lvl points from dices of cognition, knowledge and smarts attributes
     * \return numbers of lvl points to spend
     */
    qint16 generateLvlPoints();

    /*!
     * \brief Prints all attributes and all theirs abilities
     */
    void stdPrint();

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTES_H
