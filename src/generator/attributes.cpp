#include "attributes.h"

Attributes::Attributes()
{
    for(qint16 i = 0; i < 10; i++){
        attributes.push_back(Attribute(ATTRIBUTES(i)));
    }
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
