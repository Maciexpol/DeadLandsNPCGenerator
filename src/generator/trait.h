#ifndef TRAIT_H
#define TRAIT_H

#include <QString>
#include "src/serializable.h"

class Trait : Serializable
{
private:
    qint16 points{};
    QString name{};
    QString description{};

public:
    Trait(qint16 points, QString name, QString description);

    qint16 getPoints() const
        {return points;}

    QString getName() const
        {return name;}

    QString getDescription() const
        {return description;}

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // TRAIT_H
