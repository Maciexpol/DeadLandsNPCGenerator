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
    QString name;
public:
    SessionCharacter() : uniqueID(0), name("UNKNOWN"){};
    SessionCharacter(const qint32 &id, const QString &newName) : uniqueID(id), name(newName){};

    qint32 getUniqueID() const{return this->uniqueID;};
    QString getName() const{return this->name;};

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};


#endif //NPC_GENERATOR_SESSIONCHARACTER_H
