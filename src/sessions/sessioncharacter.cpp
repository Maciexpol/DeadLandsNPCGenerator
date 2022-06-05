//
// Created by Lesio on 04.06.2022.
//

#include "sessioncharacter.h"

QDomElement SessionCharacter::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("sessionCharacter");

    element.setAttribute("uniqueID", this->uniqueID);
    element.setAttribute("name", this->name);

    return element;
}

void SessionCharacter::XmlDeserialize(const QDomElement &element) {
    this->uniqueID = static_cast<qint32>(element.attribute("uniqueID", "0").toULong());
    this->name = element.attribute("name", "UNKNOWN");
}