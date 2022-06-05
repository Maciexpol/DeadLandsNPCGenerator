#include "trait.h"

Trait::Trait(qint16 inputPoints, QString inputName, QString inputDescription)
{
    points = inputPoints;
    name = inputName;
    description = inputDescription;
}

QDomElement Trait::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("trait");

    element.setAttribute("points", this->points);
    element.setAttribute("name", this->name);
    element.setAttribute("description", this->description);

    return element;
}

void Trait::XmlDeserialize(const QDomElement &element) {
    this->points = static_cast<qint16>(element.attribute("points", "0").toInt());
    this->name = element.attribute("name", "UNKNOWN");
    this->description = element.attribute("description", "UNKNOWN");
}
