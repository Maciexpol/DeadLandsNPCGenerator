#ifndef ABILITY_H
#define ABILITY_H

#include "QString"
#include <iostream>


/*!
 * \brief The Ability class
 * \brief Contains name of the ability and it's level
 *
 */
class Ability
{
private:
    QString name;
    // normally lvl would be added after the definition
    qint16 lvl;
public:
    /*!
     * \brief Creates empty ability
     */
    Ability() : name(""), lvl(0){};
    /*!
     * \brief Creates ability with specific name and lvl
     * \param newName
     * \param newLvl
     */
    Ability(const QString & newName, const qint16 & newLvl) : name(newName), lvl(newLvl){};
    /*!
     * \brief Creates ability with specific name and lvl 0
     * \param newName
     */
    Ability(const QString & newName) : name(newName), lvl(0){};

    QString getName() const {return name;};
    qint16 getLvl() const {return lvl;};

    void setLvl(const qint16 & newLvl) {lvl = newLvl;};
    void setName(const QString & newName) {name = newName;};

    /*!
     * \brief Adds one more point to level of attribute
     *
     * Needed to parrent's rolling function
     */
    void addLvlPoint() {lvl++;};

    /*!
     * \brief Zeros lvl
     */
    void clearLvl() {lvl = 0;};

    /*!
     * \brief Print ability on standard output
     */
    void stdPrint() {std::cout << name.toStdString() << " - " << lvl << std::endl;};
};

#endif // ABILITY_H
