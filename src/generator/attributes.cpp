#include "attributes.h"

Attributes::Attributes(const qint16 & characterLvlPoints, const Dices & dices){

//    return;
//    QVector<QVector<QString>> abilities{};

    QVector<QVector<QString>> abilities = MemIO::loadAbilities();
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(i)));
    }
    rollAttributesLvlPoints(characterLvlPoints);
}

Attributes::Attributes(const Dices & dices){
//    return;
//    QVector<QVector<QString>> abilities{};

    QVector<QVector<QString>> abilities = MemIO::loadAbilities();
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(i)));
    }
}

Attribute Attributes::getAttribute(ATTRIBUTES sName) const{
//    // 1 option
//    return attributes[(qint16) sName];
    // 2 option
    for(auto & at : attributes){
        if(at.getName() == sName)
            return at;
    }
    return {};
}

qint16 Attributes::generateLvlPoints(){
    qint16 sum = 0;
    sum += getAttribute(ATTRIBUTES::cognition).getDice().getSides();
    sum += getAttribute(ATTRIBUTES::knowledge).getDice().getSides();
    sum += getAttribute(ATTRIBUTES::smarts).getDice().getSides();
    return sum;
}

void Attributes::clearAttributesLvlPoints(){
    for(auto & at : attributes){
        at.clearAbilitiesLvl();
    }
}

void Attributes::rollAttributesLvlPoints(const qint16 & characterLvlPoints){
    // reseting lvl of all abilities in all attributes
    clearAttributesLvlPoints();
    // random generator init
    auto rng = std::default_random_engine {};
    // function returns random indexes of abilities
    std::uniform_int_distribution<qint16> num(0, attributes.length()-1);

    // randomly increasing abillities lvl by one
    for(qint16 i = 0; i < characterLvlPoints; i++){
        qint16 index = num(rng);
        attributes[index].increaseAbilitiesLvlSum();
    }

    // rolling abilities inside of abilities
    for(auto & at : attributes){
        at.rollAbilitiesLvl();
    }
}

void Attributes::stdPrint(){
    for(auto & at : attributes){
        at.stdPrint();
    }
}

QDomElement Attributes::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("attributes");

    for(auto &attribute : attributes){
        element.appendChild(attribute.XmlSerialize());
    }
    return element;
}

void Attributes::XmlDeserialize(const QDomElement &element) {

}
