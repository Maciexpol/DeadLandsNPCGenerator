#include "edgesandhindrances.h"

EdgesAndHindrances::EdgesAndHindrances()
{

}

qint16 EdgesAndHindrances::countBalance() const {
    qint16 edgesPoints{0};
    qint16 hindrancesPoints{0};

    for(auto trait : Edges){
        edgesPoints += trait.getPoints();
    }

    for(auto trait : Hindrances){
        hindrancesPoints+= trait.getPoints();
    }

    return hindrancesPoints - edgesPoints;

}

QDomElement EdgesAndHindrances::XmlSerialize(QDomDocument &doc) const {
    QDomElement element = doc.createElement("edgesAndHindrances");

    QDomElement edgesElement = doc.createElement("edges");
    for(auto &edge : Edges){
        edgesElement.appendChild(edge.XmlSerialize(doc));
    }

    QDomElement hindrancesElement = doc.createElement("hindrances");
    for(auto &hind : Hindrances){
        hindrancesElement.appendChild(hind.XmlSerialize(doc));
    }

    return element;
}

void EdgesAndHindrances::XmlDeserialize(const QDomElement &element) {

}
