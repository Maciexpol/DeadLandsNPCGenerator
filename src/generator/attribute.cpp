#include "attribute.h"

std::ostream& operator<<(std::ostream& out, const ATTRIBUTES value){
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(cognition);
        PROCESS_VAL(knowledge);
        PROCESS_VAL(smarts);
        PROCESS_VAL(deftness);
        PROCESS_VAL(nimbleness);
        PROCESS_VAL(vigor);
        PROCESS_VAL(spirit);
        PROCESS_VAL(mien);
        PROCESS_VAL(quickness);
        PROCESS_VAL(strength);
    }
#undef PROCESS_VAL

    return out << s;
}

void Attribute::rollAbilitiesLvl(){
    clearAbilitiesLvl();
    abilities.rollAbilitesLvl(abilitiesLvlSum);
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
    element.setAttribute("name", this->name);
    element.setAttribute("lvlSum", this->abilitiesLvlSum);
    element.appendChild(dice.XmlSerialize());
    element.appendChild(abilities.XmlSerialize());
    return element;
}

void Attribute::XmlDeserialize(const QDomElement &element) {

}



