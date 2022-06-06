#include "overview.h"

Overview::Overview()
{

}

QDomElement Overview::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("overview");

    element.setAttribute("first_name", this->first_name);
    element.setAttribute("last_name", this->last_name);
    element.setAttribute("occupation", this->occupation);
    element.setAttribute("origin", this->origin);
    element.setAttribute("age", this->age);
    return element;
}

void Overview::XmlDeserialize(const QDomElement &element) {
    this->first_name = element.attribute("first_name", "UNKNOWN");
    this->last_name = element.attribute("last_name", "UNKNOWN");
    this->occupation = element.attribute("occupation", "UNKNOWN");
    this->origin = element.attribute("origin", "UNKNOWN");
    this->age = static_cast<qint16>(element.attribute("age", "0").toInt());
}
