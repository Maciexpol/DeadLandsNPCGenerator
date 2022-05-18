#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QString>

/*!
 * \brief General information about NPC
 *
 * Holds and generated general information about NPC character such as first and last name, occupation, age etc.
 */
class Overview
{
private:
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
};

#endif // OVERVIEW_H
