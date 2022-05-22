#ifndef CHARACTER_H
#define CHARACTER_H

#include "../serializable.h"
#include "attributes.h"
#include "dices.h"


/*!
 * \brief Character data
 *
 * Holds character data and manages its' generation.
 */
class Character : Serializable
{
private:
    Attributes attributes;
    Dices dices;

public:
    Character();

    Attributes getAttributes() const{return this->attributes;}
    Dices getDices() const{return this->dices;}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;

};

#endif // CHARACTER_H
