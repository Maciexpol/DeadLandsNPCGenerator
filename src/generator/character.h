#ifndef CHARACTER_H
#define CHARACTER_H

#include "attributes.h"
#include "dices.h"
#include "hydrants.h"


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
    Hydrants hydrants;

public:
    Character();

    Attributes getAttributes() const{return this->attributes;}
    Hydrants getHydrants() const{return this->hydrants;}
    Dices getDices() const{return this->dices;}

};

#endif // CHARACTER_H
