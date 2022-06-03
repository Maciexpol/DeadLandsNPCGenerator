#include "attribute.h"

Attribute::Attribute(ATTRIBUTES inputName){
    name = inputName;
}

Attribute::Attribute(ATTRIBUTES inputName, Abilities inputAbilities){
    name = inputName;
    abilities = inputAbilities;
}

Attribute::Attribute(ATTRIBUTES inputName, Dice inputDice, Abilities inputAbilities){
    name = inputName;
    dice = inputDice;
    abilities = inputAbilities;
}

QDomElement Attribute::XmlSerialize(QDomDocument &doc) const {
    QDomElement element = doc.createElement("attribute");

    element.setAttribute("name", this->name);
    element.appendChild(dice.XmlSerialize(doc));
    element.appendChild(abilities.XmlSerialize(doc));
    return element;
}

void Attribute::XmlDeserialize(const QDomElement &element) {

}



