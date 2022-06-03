#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "dice.h"
#include "abilities.h"
#include "src/serializable.h"

enum ATTRIBUTES {
    cognition = 0,
    knowledge,
    smarts,
    deftness,
    nimbleness,
    mien,
    spirit,
    strength,
    vigor,
    quickness
};

/*!
 * \brief Represents one attribute of NPC character
 */
class Attribute : Serializable
{
private:
    ATTRIBUTES name;
    Dice dice;
    Abilities abilities;

public:
    Attribute(ATTRIBUTES inputName, Dice inputDice, Abilities inputAbilities);
    Attribute(ATTRIBUTES inputName, Abilities inputAbilities);
    Attribute(ATTRIBUTES inputName);

    Dice getDice() const{return this->dice;}
    Abilities getAbilities() const{return this->abilities;}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTE_H
