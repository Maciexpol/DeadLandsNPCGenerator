#include "edgesandhindrances.h"

EdgesAndHindrances::EdgesAndHindrances()
{
    rollEdgesAndHindrances();
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

void EdgesAndHindrances::rollEdgesAndHindrances() {
    QSqlDatabase db = QSqlDatabase::database("local");
    //TODO: Add lost connection handling
    if(!db.open())
        return;
    Edges.clear();
    Hindrances.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<qint16> num(0, 2);
    int edgesCount = num(gen);
    int hindrancesCount = num(gen);

    QSqlQuery query(db);
    //TODO: Usunąć stąd zliczanie i zrobić w innym miejscu
    int availableEdges;
    int availableHindrances;
    query.exec("SELECT COUNT(*) FROM edges");
    query.next();
    availableEdges = query.value(0).toInt();
    query.exec("SELECT COUNT(*) FROM hindrances");
    query.next();
    availableHindrances = query.value(0).toInt();

    num = std::uniform_int_distribution<qint16> (1, availableEdges);
    while(edgesCount){
        qDebug("EDGEE");
        query.exec("SELECT edge, points, description FROM edges WHERE id=" + QString::number(num(gen)));
        query.next();
        Trait newEdge(query.value(1).toInt(), query.value(0).toString(), query.value(2).toString());
        bool isIn = false;
        for(auto &i : Edges){
            if(newEdge.getName() == i.getName()){
                isIn = true;
            }
        }
        if(!isIn){
            Edges.append(newEdge);
            edgesCount--;
        }
    }
    num = std::uniform_int_distribution<qint16> (1, availableHindrances);
    while(hindrancesCount){
        qDebug("HINDRANCE");
        query.exec("SELECT hindrance, points, description FROM hindrances WHERE id=" + QString::number(num(gen)));
        query.next();
        Trait newHindrance(query.value(1).toInt(), query.value(0).toString(), query.value(2).toString());
        bool isIn = false;
        for(auto &i : Hindrances){
            if(newHindrance.getName() == i.getName()){
                isIn = true;
            }
        }
        if(!isIn){
            Hindrances.append(newHindrance);
            hindrancesCount--;
        }
    }
    std::cout << "Edges length: " << Edges.length() << std::endl;
    std::cout << "Hindrances length: " << Hindrances.length() << std::endl;
}

QDomElement EdgesAndHindrances::XmlSerialize() const {
    QDomDocument doc("");
    QDomElement element = doc.createElement("edgesAndHindrances");

    QDomElement edgesElement = doc.createElement("edges");
    for(auto &edge : Edges){
        edgesElement.appendChild(edge.XmlSerialize());
    }
    element.appendChild(edgesElement);

    QDomElement hindrancesElement = doc.createElement("hindrances");
    for(auto &hind : Hindrances){
        hindrancesElement.appendChild(hind.XmlSerialize());
    }
    element.appendChild(hindrancesElement);
    return element;
}

void EdgesAndHindrances::XmlDeserialize(const QDomElement &element) {
    QDomElement edgesElement = element.firstChildElement();
    QDomElement hindrancesElement = edgesElement.nextSiblingElement();

    Edges.clear();
    Hindrances.clear();

    QDomElement node = edgesElement.firstChildElement();
    while(!node.isNull()){
        Trait edge;
        edge.XmlDeserialize(node);
        Edges.append(edge);
        node = node.nextSiblingElement();
    }
    node = hindrancesElement.firstChildElement();
    while(!node.isNull()){
        Trait hind;
        hind.XmlDeserialize(node);
        Hindrances.append(hind);
        node = node.nextSiblingElement();
    }
}
