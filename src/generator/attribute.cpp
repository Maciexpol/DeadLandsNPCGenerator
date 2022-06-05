#include "attribute.h"

void Attribute::rollAbilitiesLvl(){
    clearAbilitiesLvl();
    abilities.rollAbilitesLvl(abilitiesLvlSum);
}

void Attribute::rollAbilitiesLvl(qint16 newAbilitiesLvlSum){
    setAbilitiesLvlSum(newAbilitiesLvlSum);
    rollAbilitiesLvl();
}

QDomElement Attribute::XmlSerialize() const {
    QDomElement element;
    element.setTagName("attribute");

    element.setAttribute("name", this->name);
    element.appendChild(dice.XmlSerialize());
    element.appendChild(abilities.XmlSerialize());
    return element;
}

void Attribute::XmlDeserialize(const QDomElement &element) {

}



