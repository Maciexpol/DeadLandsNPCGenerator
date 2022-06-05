#ifndef ABILITIES_H
#define ABILITIES_H


#include <random>
#include "ability.h"
#include "QVector"
#include "QString"
#include "src/serializable.h"
/*!
 * \brief The Abilities class
 * \brief Contains QVector of abilities, can roll stats lvl
 *
 * Rolling function gets number of points which needs to be randomly distributed between abilities lvl
 */
class Abilities : Serializable
{
private:
    QVector<Ability> abilities;
public:
    /*!
     * \brief Creates empty abilities element
     */
    Abilities(){};
    /*!
     * \brief Creates abilities with given names and 0 lvl
     * \param names
     */
    Abilities(const QVector<QString> & names);

    /*!
     * \brief Adds ability to abilities vector
     * \param newAbility
     */
    void addAbility(const Ability & newAbility) {abilities.push_back(newAbility);};
    /*!
     * \brief Creates new ability with specific name and 0 lvl
     * \param newAbilityName
     */
    void addAbility(const QString & newAbilityName) {abilities.push_back(Ability(newAbilityName));};
    /*!
     * \brief Creates new ability with specific name and lvl
     * \param newAbilityName
     * \param newAbilityLvl
     */
    void addAbility(const QString & newAbilityName, const qint16 & newAbilityLvl) {abilities.push_back(Ability(newAbilityName, newAbilityLvl));};
    /*!
     * \brief Removes ability with specific name
     * \param name
     */
    void removeAbility(const QString & name);
    void setAbilities(const QVector<QString> & names);

    /*!
     * \brief Zeros lvl of all abilities
     */
    void clearLvl();


    qint16 getAbilityLevel(const QString & name) const;
    qint16 getAbilityLevel(const qint16 & index) const {return abilities[index].getLvl();};
    QVector<Ability> getAbilites() const {return abilities;};

    /*!
     * \brief Rolls *points* times which ability needs to gain one more lvl point
     * \param points
     */
    void rollAbilitesLvl(const qint16 & points);

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ABILITIES_H
