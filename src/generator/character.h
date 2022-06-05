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
    // Remember to serialize newly added objects in XmlSerialize
    qint32 uniqueID;
    Attributes attributes;
    Dices dices;
    EdgesAndHindrances edgesAndHindrances;
    Overview overview;

public:
    Character();
    
    qint32 getUniqueID() const {return this->uniqueID;};
    Attributes getAttributes() const{return this->attributes;}
    Dices getDices() const{return this->dices;};

    void stdPrint();

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
    bool XmlValidate() const override;

    void rollCharacter();
    void rollDices();
};

#endif // CHARACTER_H
