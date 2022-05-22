#include "character.h"

Character::Character()
{
    Character::rollDices();
}

void Character::rollDices(){
    dices.rollDices();
}

QDomElement Character::XmlSerialize(QDomDocument &doc) const{

};

void Character::XmlDeserialize(const QDomElement &element){};
