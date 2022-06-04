#include "session.h"
#include "sessioncharacter.h"
Session::Session() = default;
Session::Session(const QString &name, const QString &description, const QDate &date, const qint16 &npcCount){
    this->name = name;
    this->description = description;
    this->creationDate = date;
    this->npcCount = npcCount;
}

void Session::addCharacter(const qint32 &id, const QString &name) {
    this->characters.append(SessionCharacter(id, name));
}

QDomElement Session::XmlSerialize(QDomDocument &doc) const{
    // Create session element and add basic attributes
    QDomElement element = doc.createElement("session");
    element.setAttribute("name", this->name);
    element.setAttribute("description", this->description);
    element.setAttribute("creationDate", this->creationDate.toString());
    element.setAttribute("npcCount", this->npcCount);

    // Serialize all characters in this session
    QDomElement npcs = doc.createElement("characters");
    for(auto &npc : this->characters){
        npcs.appendChild(npc.XmlSerialize(doc));
    }

    // Add serialized characters
    element.appendChild(npcs);
    return element;
}

void Session::XmlDeserialize(const QDomElement &element){
    this->name = element.attribute("name", "-");
    this->description = element.attribute("description", "-");
    this->creationDate = QDate::fromString(element.attribute("creationDate", ""));
    this->npcCount = static_cast<qint16>(element.attribute("npcCount", "0").toInt());

    //TODO: Add deserialization of characters
}

bool Session::XmlValidate() const {
    if(this->name.isEmpty()) return false;
    return true;
}
