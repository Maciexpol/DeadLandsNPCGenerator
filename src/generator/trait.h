#ifndef TRAIT_H
#define TRAIT_H

#include <QString>

class Trait
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

};

#endif // TRAIT_H
