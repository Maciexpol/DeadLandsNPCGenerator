//
// Created by Lesio on 04.06.2022.
//

#include "sessioncharacter.h"

QString SessionCharacter::toStr() const{
    //return uniqueID+"_"+this->first_name+"_"+this->last_name;
    return uniqueID;
}

QDomElement SessionCharacter::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("sessionCharacter");

    element.setAttribute("uniqueID", this->uniqueID);
    element.setAttribute("firstName", this->first_name);
    element.setAttribute("lastName", this->last_name);

    return element;
}

void SessionCharacter::XmlDeserialize(const QDomElement &element) {
    this->uniqueID = element.attribute("uniqueID", "");
    this->first_name = element.attribute("firstName", "UNKNOWN");
    this->last_name = element.attribute("lastName", "UNKNOWN");
}