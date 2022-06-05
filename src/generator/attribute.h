#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "dice.h"
#include "abilities.h"
#include "src/serializable.h"

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
class Attribute : Serializable
{
private:
    qint16 abilitiesLvlSum;
    ATTRIBUTES name;
    Dice dice;
    Abilities abilities;

public:
    /*!
     * \brief Creates empty attribute
     */
    Attribute()
        {name = ATTRIBUTES(0); dice = Dice(0); abilities = Abilities(); abilitiesLvlSum = 0;};
    /*!
     * \brief Creates attribute with name, abilities, dice, but without abilities lvl points
     * \param inputName
     * \param abilitiesNames
     * \param inputDice
     */
    Attribute(const ATTRIBUTES & inputName, const QVector<QString> & abilitiesNames, const Dice & inputDice)
        {name = inputName; dice = inputDice; abilities = Abilities(abilitiesNames); abilitiesLvlSum = 0;};
    /*!
     * \brief Creates attribute with name, abilities, dice, abilities lvl points
     * \param inputName
     * \param abilitiesNames
     * \param inputDice
     * \param newAbilitiesLvlSum
     */
    Attribute(const ATTRIBUTES & inputName, const QVector<QString> & abilitiesNames, const Dice & inputDice, const qint16 & newAbilitiesLvlSum)
        {name = inputName; dice = inputDice; abilities = Abilities(abilitiesNames); abilitiesLvlSum = newAbilitiesLvlSum;};

    /*!
     * \brief Tells if we have any abilities
     * \return status of having abilities
     */
    bool hasAbilities()
        {return (bool)abilities.getAbilites().length();};

    void setName(const ATTRIBUTES & newName) {name = newName;};
    void setDice(const Dice & newDice) {dice = newDice;};
    void setAbilities(const QVector<QString> & abilitiesNames){abilities.setAbilities(abilitiesNames);};
    void setAbilitiesLvlSum(const qint16 & newSum) {abilitiesLvlSum = newSum;};

    /*!
     * \brief Increases abilitiesLvlSum by one
     * Needed for parrent's rolling function
     */
    void increaseAbilitiesLvlSum() {abilitiesLvlSum++;};
    /*!
     * \brief Zeros all abilities lvl
     */
    void clearAbilitiesLvl() {abilities.clearLvl();};


    ATTRIBUTES getName() const {return name;};
    Dice getDice() const {return dice;};
    Abilities getAbilities() const {return abilities;};
    qint16 getabilitiesLvlSum() const {return abilitiesLvlSum;};


    /*!
     * \brief Takes abilitiesLvlSum and calls abilities rollAbilitesLvl method
     */
    void rollAbilitiesLvl();
    /*!
     * \brief Does the same as basic fucntion call and setAbilitiesLvlSum at once
     * \param newAbilitiesLvlSum
     */
    void rollAbilitiesLvl(qint16 newAbilitiesLvlSum);

    /*!
     * \brief Print whole character on standard output with all it's abilities
     */
    void stdPrint();

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ATTRIBUTE_H
