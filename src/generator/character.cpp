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

void Character::updateInfo() {
    emit updateCharacterInfo(*this);
}

QString Character::toStr() const{
    return QString::number(uniqueID)+"_"+this->overview.getFirstName()+"_"+this->overview.getLastName();
}

//SessionCharacter Character::toSessionCharacter() const {
//}

void Character::saveCharacter() {
    MemIO::saveCharacter(this->XmlSerialize());
}

void Character::addCharacterToSession() {
    SessionCharacter character(this->uniqueID, this->overview.getFirstName(), this->overview.getLastName());
    saveCharacter();
    emit addCharacter(character);
}

void Character::generateCharacter() {
    this->rollCharacter();
    updateInfo();
}

void Character::loadCharacter(const SessionCharacter &character) {
    QDomElement node = MemIO::loadCharacter(character.toStr());
    this->XmlDeserialize(node);
    updateInfo();
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

    element.setNodeValue(this->toStr());

    return element;
};

void Character::XmlDeserialize(const QDomElement &element){
    this->uniqueID = static_cast<qint32>(element.attribute("uniqueID", "0").toInt());
    QDomElement node;
    overview.XmlDeserialize(node = element.firstChildElement());
    attributes.XmlDeserialize(node = node.nextSiblingElement());
    dices.XmlDeserialize(node = node.nextSiblingElement());
    edgesAndHindrances.XmlDeserialize(node = node.nextSiblingElement());
};

bool Character::XmlValidate() const {return true;}

void Character::rollSpecificAbility(const ATTRIBUTES & name){
    this->attributes.getAttribute(name)->stdPrint();
    this->attributes.getAttribute(name)->rollAbilitiesLvl();
    this->attributes.getAttribute(name)->stdPrint();
    emit updateCharacterInfo(*this);
}

void Character::rollFromLvlPoints(){
    attributes.clearAttributesLvlSum();
    attributes.rollAttributesLvlPoints(attributes.generateLvlPoints());
    emit updateCharacterInfo(*this);
}

void Character::rollFromOverview(){
    overview.rollOverview();
    emit updateCharacterInfo(*this);
}

void Character::rollFromName(){
    emit updateCharacterInfo(*this);
}

void Character::rollAge(){

    emit updateCharacterInfo(*this);
}

void Character::rollOccupation(){

    emit updateCharacterInfo(*this);
}

void Character::rollFromOrigin(){

    emit updateCharacterInfo(*this);
}
