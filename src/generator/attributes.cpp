#include "attributes.h"

Attributes::Attributes(const qint16 & characterLvlPoints, const Dices & dices){
    QVector<QVector<QString>> abilities = loadAbilities();
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(i)));
    }
    rollAttributesLvlPoints(characterLvlPoints);
}

void Attributes::clearAttributesLvlPoints(){
    for(auto & at : attributes){
        at.setAbilitiesLvlSum(0);
    }
}

void Attributes::rollAttributesLvlPoints(const qint16 & characterLvlPoints){
    // random generator init
    auto rng = std::default_random_engine {};
    // function returns random indexes of abilities
    std::uniform_int_distribution<qint16> num(0, attributes.length());

    // randomly increasing abillities lvl by one
    for(qint16 i = 0; i < characterLvlPoints; i++){
        qint16 index = num(rng);
        attributes[index].increaseAbilitiesLvlSum();
    }

}

QDomElement Attributes::XmlSerialize(QDomDocument &doc) const {
    QDomElement element = doc.createElement("attributes");

    for(auto &attribute : attributes){
        element.appendChild(attribute.XmlSerialize(doc));
    }
    return element;
}

void Attributes::XmlDeserialize(const QDomElement &element) {

}
