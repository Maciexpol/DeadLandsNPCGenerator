#include "attribute.h"

void Attribute::rollAbilitiesLvl(){
    abilities.rollAbilitesLvl(abilitiesLvlSum);
}

void Attribute::rollAbilitiesLvl(qint16 newAbilitiesLvlSum){
    setAbilitiesLvlSum(newAbilitiesLvlSum);
    rollAbilitiesLvl();
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



