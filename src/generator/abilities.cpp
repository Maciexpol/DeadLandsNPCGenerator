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

void Abilities::clearAbilitiesLvlPoints(){
    for(auto & ab : abilities){
        ab.setLvl(0);
    }
}

void Abilities::rollAbilitesLvl(const qint16 & points){
    // cleaning abilities
    clearAbilitiesLvlPoints();
    // random generator init
    auto rng = std::default_random_engine {};
    // function returns random indexes of abilities
    std::uniform_int_distribution<qint16> num(0, abilities.length()-1);

    // randomly increasing abillities lvl by one
    for(qint16 i = 0; i < points; i++){
        qint16 index = num(rng);
        abilities[index].addLvlPoint();
    }
}

QDomElement Abilities::XmlSerialize(QDomDocument &doc) const {
    return {};
}

void Abilities::XmlDeserialize(const QDomElement &element) {

}
