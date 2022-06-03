#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QString>
#include "/src/serializable.h"

/*!
 * \brief General information about NPC
 *
 * Holds and generated general information about NPC character such as first and last name, occupation, age etc.
 */
class Overview : Serializable
{
private:
    // Remember to serialize newly added objects in XmlSerialize
    QString first_name;
    QString last_name;
    QString occupation;
    QString origin;
    qint16 age;


public:
    Overview();

    QString getFirstName() const{return this->first_name;}
    QString getLastName() const{return this->last_name;}
    QString getOccupation() const{return this->occupation;}
    QString getOrigin() const{return this->origin;}
    qint16 getAge() const{return this->age;}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // OVERVIEW_H
