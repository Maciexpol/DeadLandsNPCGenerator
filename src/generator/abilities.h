#ifndef ABILITIES_H
#define ABILITIES_H

#include <random>
#include "ability.h"
#include "QVector"
#include "QString"

/*!
 * \brief The Abilities class
 * \brief Contains QVector of abilities, can roll stats lvl
 *
 * Rolling function gets number of points which needs to be randomly distributed between abilities lvl
 */

class Abilities
{
private:
    QVector<Ability> abilities;
public:
    /*!
     * \brief Abilities
     *
     * Creates empty abilities element
     */
    Abilities(){};
    /*!
     * \brief Abilities
     * \param names
     *
     * Creates abilities with given names and 0 lvl
     */
    Abilities(const QVector<QString> & names);

    /*!
     * \brief addAbility
     * \param newAbility
     *
     * Adds ability to abilities vector
     */
    void addAbility(const Ability & newAbility) {abilities.push_back(newAbility);};
    /*!
     * \brief addAbility
     * \param newAbilityName
     *
     * Creates new ability with specific name and 0 lvl
     */
    void addAbility(const QString & newAbilityName) {abilities.push_back(Ability(newAbilityName));};
    /*!
     * \brief addAbility
     * \param newAbilityName
     * \param newAbilityLvl
     *
     * Creates new ability with specific name and lvl
     */
    void addAbility(const QString & newAbilityName, const qint16 & newAbilityLvl) {abilities.push_back(Ability(newAbilityName, newAbilityLvl));};
    /*!
     * \brief removeAbility
     * \param name
     *
     * Removes ability with specific name
     */
    void removeAbility(const QString & name);
    /*!
     * \brief setAbilities
     * \param vector with names of abilities
     *
     * Creates abilities
     */
    void setAbilities(const QVector<QString> & names);

    /*!
     * \brief getAbilityLevel
     * \param name
     * \return level of ability with specific name
     */
    qint16 getAbilityLevel(const QString & name) const;
    /*!
     * \brief getAbilityLevel
     * \param index
     * \return level of ability at sepcific index
     */
    qint16 getAbilityLevel(const qint16 & index) const {return abilities[index].getLvl();};
    /*!
     * \brief getAbilites
     * \return vector with abilities
     */
    QVector<Ability> getAbilites() const {return abilities;};
    /*!
     * \brief rollAbilitesLvl
     * \param points
     *
     * Rolls *points* times which ability needs to gain one more lvl point
     */
    void rollAbilitesLvl(const qint16 & points);
};

#endif // ABILITIES_H
