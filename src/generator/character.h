#ifndef CHARACTER_H
#define CHARACTER_H

#include "src/serializable.h"
#include "attributes.h"
#include "dices.h"
#include "edgesandhindrances.h"
#include "overview.h"
#include "rolldices.h"

/*!
 * \brief Character data
 *
 * Holds character data and manages its' generation.
 */
class Character : Serializable
{
private:
//    Remember to serialize newly added objects in XmlSerialize
    Attributes attributes;
    Dices dices;
    EdgesAndHindrances edgesAndHindrances;
    Overview overview;

public:
    Character();

    void rollCharacter();

    Attributes getAttributes() const{return this->attributes;}
    Dices getDices() const{return this->dices;}

    void rollDices();

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // CHARACTER_H
