//
// Created by Lesio on 04.06.2022.
//

#ifndef NPC_GENERATOR_SESSIONCHARACTER_H
#define NPC_GENERATOR_SESSIONCHARACTER_H

#include "src/serializable.h"
#include <QString>

class SessionCharacter : Serializable
{
private:
    qint32 uniqueID;
    QString first_name;
    QString last_name;
public:
    SessionCharacter() : uniqueID(0), first_name("UNKNOWN"), last_name("UNKNOWN"){};
    SessionCharacter(const qint32 &id, const QString &newFirstName, const QString &newLastName) :
        uniqueID(id),
        first_name(newFirstName),
        last_name(newLastName)
        {};

    qint32 getUniqueID() const{return this->uniqueID;};
    QString getFirstName() const{return this->first_name;};
    QString getLastName() const{return this->last_name;};

    //Reimplement this function also in Character
    QString toStr() const;

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};


#endif //NPC_GENERATOR_SESSIONCHARACTER_H
