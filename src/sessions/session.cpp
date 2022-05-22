#include "session.h"

Session::Session()
{

}

Session::Session(const QString name, const QString description, const QDate date, const qint16 npcCount){
    this->name = name;
    this->description = description;
    this->creationDate = date;
    this->npcCount = npcCount;
}

QDomElement Session::XmlSerialize(QDomDocument &doc) const{
    QDomElement element = doc.createElement("session");
    QDomElement name = doc.createElement("name");
    QDomElement description = doc.createElement("description");
    QDomElement date = doc.createElement("creationDate");
    QDomElement npcCount = doc.createElement("npcCount");
    name.appendChild(doc.createTextNode(this->name));
    description.appendChild(doc.createTextNode(this->description));
    date.appendChild(doc.createTextNode(this->getCreationDate().toString()));
    npcCount.appendChild(doc.createTextNode(QString::number(this->npcCount)));
    element.appendChild(name);
    element.appendChild(description);
    element.appendChild(date);
    element.appendChild(npcCount);
    return element;
}

void Session::XmlDeserialize(const QDomElement) const{

}
