#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "dice.h"
#include "ability.h"

/*!
 * \brief Represents one attribute of NPC character
 */
class Attribute
{
private:
    Dice dice;
    Ability ability;

public:
    Attribute();

    Dice getDice() const{return this->dice;}
    Ability getAbility() const{return this->ability;}
};

#endif // ATTRIBUTE_H
