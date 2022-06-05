#include "edgesandhindrances.h"

EdgesAndHindrances::EdgesAndHindrances()
{

}

qint16 EdgesAndHindrances::countPoints(const QVector<Trait> & traits) const{
    if(traits.length() == 0)
        return 0;

    qint16 points = 0;

    for(auto trait : Edges){
        points += trait.getPoints();
    }
    return points;
}

qint16 EdgesAndHindrances::countBalance() const {
    qint16 edgesPoints = countPoints(Edges);
    qint16 hindrancesPoints = countPoints(Hindrances);

    return hindrancesPoints - edgesPoints;

}

QDomElement EdgesAndHindrances::XmlSerialize() const {
    QDomDocument doc("");
    QDomElement element = doc.createElement("edgesAndHindrances");

    QDomElement edgesElement = doc.createElement("edges");
    for(auto &edge : Edges){
        edgesElement.appendChild(edge.XmlSerialize());
    }

    QDomElement hindrancesElement = doc.createElement("hindrances");
    for(auto &hind : Hindrances){
        hindrancesElement.appendChild(hind.XmlSerialize());
    }
    return element;
}

void EdgesAndHindrances::XmlDeserialize(const QDomElement &element) {

}
