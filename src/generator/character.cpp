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

QDomElement Character::XmlSerialize(QDomDocument &doc) const{
    // Create character element
    QDomElement element = doc.createElement("character");
    // Serialize Overview
    element.appendChild(this->overview.XmlSerialize(doc));
    // Serialize Attributes
    element.appendChild(this->attributes.XmlSerialize(doc));
    // Serialize Dices
    element.appendChild(this->dices.XmlSerialize(doc));
    // Serialize EdgesAndHindrances
    element.appendChild(this->edgesAndHindrances.XmlSerialize(doc));

    return element;
};

void Character::XmlDeserialize(const QDomElement &element){};

bool Character::XmlValidate() const {return true;};
