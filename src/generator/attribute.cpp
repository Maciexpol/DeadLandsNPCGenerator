#include "attribute.h"

std::ostream& operator<<(std::ostream& out, const ATTRIBUTES value){
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(Cognition);
        PROCESS_VAL(Knowledge);
        PROCESS_VAL(Smarts);
        PROCESS_VAL(Deftness);
        PROCESS_VAL(Nimbleness);
        PROCESS_VAL(Vigor);
        PROCESS_VAL(Spirit);
        PROCESS_VAL(Mien);
        PROCESS_VAL(Quickness);
        PROCESS_VAL(Strength);
    }
#undef PROCESS_VAL

    return out << s;
}

void Attribute::rollAbilitiesLvl(){
    std::cout << "the rolling is starting" << std::endl;
    if(hasAbilities()){
        clearAbilitiesLvl();
        abilities.rollAbilitesLvl(abilitiesLvlSum);
    }
}

void Attribute::rollAbilitiesLvl(qint16 newAbilitiesLvlSum){
    setAbilitiesLvlSum(newAbilitiesLvlSum);
    rollAbilitiesLvl();
}

void Attribute::stdPrint(){
    std::cout << name << " - " << dice << "  - got " << abilitiesLvlSum << " Lvlpoints" << std::endl;
    abilities.stdPrint();
}

QDomElement Attribute::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("attribute");

    // WARNING: Dealing with enum, might not work
    element.setAttribute("name", (static_cast<qint16>(this->name)));
    element.setAttribute("lvlSum", this->abilitiesLvlSum);
    element.appendChild(dice.XmlSerialize());
    element.appendChild(abilities.XmlSerialize());
    return element;
}

void Attribute::XmlDeserialize(const QDomElement &element) {
    this->name = static_cast<ATTRIBUTES>(element.attribute("name", "UNKNOWN").toInt());
    this->abilitiesLvlSum = static_cast<qint16>(element.attribute("lvlSum", "0").toInt());
    QDomElement node;
    this->dice.XmlDeserialize(node = element.firstChildElement());
    this->abilities.XmlDeserialize(node = node.nextSiblingElement());
}



