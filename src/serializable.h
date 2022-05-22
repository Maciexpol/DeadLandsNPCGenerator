#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QString>
#include <QtXml\QDomDocument>

class Serializable
{
public:
    virtual QDomElement XmlSerialize(QDomDocument &doc) const = 0;
    virtual void XmlDeserialize(const QDomElement element) const = 0;
};

#endif // SERIALIZABLE_H
