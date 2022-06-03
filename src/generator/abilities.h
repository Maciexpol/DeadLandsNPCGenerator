#ifndef ABILITIES_H
#define ABILITIES_H

#include "/src/serializable.h"

class Abilities : Serializable
{
public:
    Abilities();

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // ABILITIES_H
