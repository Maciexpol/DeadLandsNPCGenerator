#include "overview.h"

Overview::Overview()
{

}

QDomElement Overview::XmlSerialize() const {
    QDomElement element;
    element.setTagName("overview");

    element.setAttribute("first_name", this->first_name);
    element.setAttribute("last_name", this->last_name);
    element.setAttribute("occupation", this->occupation);
    element.setAttribute("origin", this->origin);
    element.setAttribute("age", this->age);
    return element;
}

void Overview::XmlDeserialize(const QDomElement &element) {
    this->first_name = element.attribute("first_name", "MISSING");
    this->last_name = element.attribute("last_name", "MISSING");
    this->occupation = element.attribute("occupation", "MISSING");
    this->origin = element.attribute("origin", "MISSING");
    this->age = static_cast<qint16>(element.attribute("age", "0").toInt());
}
