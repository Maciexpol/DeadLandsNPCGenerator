#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "dice.h"
#include "abilities.h"

enum ATTRIBUTES {
    cognition = 0,
    knowledge,
    smarts,
    deftness,
    nimbleness,
    mien,
    spirit,
    strength,
    vigor,
    quickness
};

/*!
 * \brief The Attribute class
 * \brief Represents one attribute of NPC character, stores abilities of this attribute, can reroll abilities lvl
 *
 * Uses Abilities class to contain abilities, also uses it to roll abilities lvl points
 * Uses attributes enum with names to store it's name
 * Uses Dice class to store dice type
 */
class Attribute
{
private:
    ATTRIBUTES name;
    Dice dice;
    Abilities abilities;
    qint16 abilitiesLvlSum;

public:
    /*!
     * \brief Attribute
     *
     * Creates empty attribute
     */
    Attribute()
        {name = ATTRIBUTES(0); dice = Dice(0); abilities = Abilities(); abilitiesLvlSum = 0;};
    /*!
     * \brief Attribute
     * \param inputName
     * \param abilitiesNames
     * \param inputDice
     *
     * Creates attribute with name, abilities, dice, but without abilities lvl points
     */
    Attribute(const ATTRIBUTES & inputName, const QVector<QString> & abilitiesNames, const Dice & inputDice)
        {name = inputName; dice = inputDice; abilities = Abilities(abilitiesNames); abilitiesLvlSum = 0;};
    /*!
     * \brief Attribute
     * \param inputName
     * \param abilitiesNames
     * \param inputDice
     * \param newAbilitiesLvlSum
     *
     * Creates attribute with name, abilities, dice, abilities lvl points
     */
    Attribute(const ATTRIBUTES & inputName, const QVector<QString> & abilitiesNames, const Dice & inputDice, const qint16 & newAbilitiesLvlSum)
        {name = inputName; dice = inputDice; abilities = Abilities(abilitiesNames); abilitiesLvlSum = newAbilitiesLvlSum;};
    /*!
     * \brief setName
     * \param new attribute name
     */
    void setName(const ATTRIBUTES & newName) {name = newName;};
    /*!
     * \brief setDice
     * \param new Dice type
     */
    void setDice(const Dice & newDice) {dice = newDice;};
    /*!
     * \brief setAbilities
     * \param all abilities names
     */
    void setAbilities(const QVector<QString> & abilitiesNames){abilities.setAbilities(abilitiesNames);};
    /*!
     * \brief setAbilitiesLvlSum
     * \param new lvl points to distribute between abilities
     */
    void setAbilitiesLvlSum(const qint16 & newSum) {abilitiesLvlSum = newSum;};
    /*!
     * \brief addAbilitiesLvlSum
     *
     * Increases abilitiesLvlSum by one
     *
     * Needed for parrent's rolling function
     */
    void addAbilitiesLvlSum() {abilitiesLvlSum++;};

    /*!
     * \brief getName
     * \return attribute's name
     */
    ATTRIBUTES getName() const {return name;};
    /*!
     * \brief getDice
     * \return attribute's dice
     */
    Dice getDice() const {return dice;};
    /*!
     * \brief getAbilities
     * \return class which contains all attribute's abilities
     */
    Abilities getAbilities() const {return abilities;};
    /*!
     * \brief getabilitiesLvlSum
     * \return sum of lvl points from all attribute's abilities
     */
    qint16 getabilitiesLvlSum() const {return abilitiesLvlSum;};
    /*!
     * \brief rollAbilitiesLvl
     *
     * Takes param abilitiesLvlSum and calls abilities rollAbilitesLvl function
     */
    void rollAbilitiesLvl();
    /*!
     * \brief rollAbilitiesLvl
     * \param newAbilitiesLvlSum
     *
     * Does the same as basic fucntion call and setAbilitiesLvlSum at once
     */
    void rollAbilitiesLvl(qint16 newAbilitiesLvlSum);
};

#endif // ATTRIBUTE_H
