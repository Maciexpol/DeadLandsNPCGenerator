#ifndef ABILITY_H
#define ABILITY_H

#include "QString"


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
     * \brief Ability
     *
     * Creates empty ability
     */
    Ability() : name(""), lvl(0){};
    /*!
     * \brief Ability
     * \param newName
     * \param newLvl
     *
     * Creates ability with specific name and lvl
     */
    Ability(const QString & newName, const qint16 & newLvl) : name(newName), lvl(newLvl){};
    /*!
     * \brief Ability
     * \param newName
     *
     * Creates ability with specific name and lvl 0
     * Most common and recommended
     */
    Ability(const QString & newName) : name(newName), lvl(0){};

    /*!
     * \brief getName
     * \return abilitie's name
     */
    QString getName() const {return name;};
    /*!
     * \brief getLvl
     * \return abilitie's lvl
     */
    qint16 getLvl() const {return lvl;};

    /*!
     * \brief setLvl
     * \param new lvl
     */
    void setLvl(const qint16 & newLvl) {lvl = newLvl;};
    /*!
     * \brief setName
     * \param new name
     */
    void setName(const QString & newName) {name = newName;};

    /*!
     * \brief addLvlPoint
     *
     * Adds one more point to level of attribute
     *
     * Needed to parrent's rolling function
     */
    void addLvlPoint() {lvl++;};
};

#endif // ABILITY_H
