#include "abilities.h"

Abilities::Abilities(const QVector<QString> & names){
    setAbilities(names);
}

void Abilities::setAbilities(const QVector<QString> & names){
    for(const auto & name : names){
        abilities.push_back(Ability(name));
    }
}

void Abilities::removeAbility(const QString & name){
    for(qint16 i = 0; i < abilities.length(); i++){
        if(abilities[i].getName() == name){
            abilities.removeAt(i);
        }
    }
}

qint16 Abilities::getAbilityLevel(const QString & name) const{
    for(const auto & ability : abilities){
        if(ability.getName() == name){
            return ability.getLvl();
        }
    }
    return 0;
}

void Abilities::clearLvl(){
    for(auto & ab : abilities){
        ab.clearLvl();
    }
}

void Abilities::rollAbilitesLvl(const qint16 & points){
    // cleaning abilities
    clearLvl();

    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> num(0, abilities.length()-1); // distribute results between 1 and 6 inclusive.

    // randomly increasing abillities lvl by one
    for(qint16 i = 0; i < points; i++){
        qint16 index = num(gen);
        while(abilities[index].getLvl() >= maxAbilityLvl)
            index = num(gen);
        abilities[index].addLvlPoint();
    }
}

void Abilities::stdPrint(){
    for(auto & ab : abilities){
        std::cout << "\t";
        ab.stdPrint();
    }
}

QDomElement Abilities::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("abilities");
    for(auto &ability : this->abilities){
        element.appendChild(ability.XmlSerialize());
    }
    return element;
}

void Abilities::XmlDeserialize(const QDomElement &element) {
    abilities.clear();
    QDomElement node = element.firstChildElement();
    while(!node.isNull()){
        Ability ability;
        ability.XmlDeserialize(node);
        abilities.append(ability);
        node = node.nextSiblingElement();
    }
}
