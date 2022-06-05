#include "ability.h"

QDomElement Ability::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("ability");
    element.setAttribute("name", this->name);
    element.setAttribute("lvl", this->lvl);

    return element;
}

void Ability::XmlDeserialize(const QDomElement &element) {
    this->name = element.attribute("name", "UNKNOWN");
    this->lvl = static_cast<qint16>(element.attribute("lvl", "0").toInt());
}