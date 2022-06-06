#include "character.h"

Character::Character()
{
    rollDices();

    attributes = Attributes(dices);

    edgesAndHindrances = EdgesAndHindrances(); //TODO:

    qint16 lvlPoints = attributes.generateLvlPoints();
    lvlPoints -= edgesAndHindrances.countBalance();
    attributes.rollAttributesLvlPoints(lvlPoints);

    overview = Overview();
}

void Character::rollCharacter(){
    rollDices();

    attributes = Attributes(dices);

    edgesAndHindrances = EdgesAndHindrances(); //TODO:

    qint16 lvlPoints = attributes.generateLvlPoints();
    lvlPoints -= edgesAndHindrances.countBalance();
    attributes.rollAttributesLvlPoints(lvlPoints);

    overview = Overview();
}

void Character::rollDices(){
    dices.rollDices();
}

void Character::stdPrint(){
    // TODO:
    //  1. print overview + ID
    //  2. print dices
    //  3. print attributes and abilities
    //  4. print edges and hindrances

    // 2. print dices
    dices.stdPrint();

    // 3. print attributes and abilities
    attributes.stdPrint();
}

void Character::addCharacterToSession() {
    SessionCharacter character(this->uniqueID, "Kurwibąk" + this->overview.getFirstName());
    emit addCharacter(character);
}

void Character::generateCharacter() {
    this->rollCharacter();
}

void Character::loadCharacter(const SessionCharacter &) {

}

QDomElement Character::XmlSerialize() const{
    // Create character element
    QDomElement element = QDomDocument().createElement("character");

    element.setAttribute("uniqueID", this->uniqueID);

    // Serialize Overview
    element.appendChild(this->overview.XmlSerialize());
    // Serialize Attributes
    element.appendChild(this->attributes.XmlSerialize());
    // Serialize Dices
    element.appendChild(this->dices.XmlSerialize());
    // Serialize EdgesAndHindrances
    element.appendChild(this->edgesAndHindrances.XmlSerialize());

    return element;
};

void Character::XmlDeserialize(const QDomElement &element){};

bool Character::XmlValidate() const {return true;}
