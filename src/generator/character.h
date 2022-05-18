#ifndef CHARACTER_H
#define CHARACTER_H

#include "hydrants.h"

/*!
 * \brief The Character class
 *
 * Holds character data and manages its' generation.
 */
class Character
{
private:
    Hydrants hydrants;

public:
    Character();

    //! Returns Hydrants of the character
    void getHydrants() const{return this->getHydrants();}
};

#endif // CHARACTER_H
