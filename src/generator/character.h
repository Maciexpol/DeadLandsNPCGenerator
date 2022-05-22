#ifndef CHARACTER_H
#define CHARACTER_H

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
class Character
{
private:
    Attributes attributes;
    Dices dices;
    EdgesAndHindrances edgesAndHindrances;
    Overview overview;

public:
    Character();

    Attributes getAttributes() const{return this->attributes;}
    Dices getDices() const{return this->dices;}

    void rollDices();

};

#endif // CHARACTER_H
