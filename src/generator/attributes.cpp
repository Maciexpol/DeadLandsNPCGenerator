#include "attributes.h"

Attributes::Attributes(const qint16 & characterLvlPoints, const Dices & dices){
    QVector<QVector<QString>> abilities = loadAbilities();
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i), abilities[i], dices.getDice(i)));
    }
    rollAttributesLvlPoints(characterLvlPoints);
}

void rollAttributesLvlPoints(const qint16 & characterLvlPoints){

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
