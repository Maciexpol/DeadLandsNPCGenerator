#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <random>
#include "src/serializable.h"
#include <iostream>

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
    qint16 originID;
    qint16 age;
    qint8 gender;

public:
    Overview();

    QString getFirstName() const{return this->first_name;}
    QString getLastName() const{return this->last_name;}
    QString getOccupation() const{return this->occupation;}
    QString getOrigin() const{return this->origin;}
    qint16 getAge() const{return this->age;}

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;

    void rollOverview();
    void rollAge();
    void rollOrigin();
    void rollOccupation();
    void rollGender();
    void rollFirstName();
    void rollLastName();
};

#endif // OVERVIEW_H
