#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "dice.h"
#include "abilities.h"

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
class Attribute
{
private:
    ATTRIBUTES name;
    Dice dice;
    Abilities abilities;

public:
    Attribute();
    Attribute(ATTRIBUTES name, Dice dice, Abilities abilities);

    Dice getDice() const{return this->dice;}
    Abilities getAbilities() const{return this->abilities;}
};

#endif // ATTRIBUTE_H
