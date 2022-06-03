#ifndef EDGESANDHINDRANCES_H
#define EDGESANDHINDRANCES_H

#include <QVector>
#include "trait.h"
#include "/src/serializable.h"

class EdgesAndHindrances : Serializable
{
private:
    QVector<Trait> Edges{};
    QVector<Trait> Hindrances{};

    qint16 countPoints() const;

public:
    EdgesAndHindrances();

    qint16 countBalance() const;

    void addEdge(Trait a)
        {Edges.push_back(a);}

    void addHindrance(Trait a)
        {Hindrances.push_back(a);}

    void clearEdges()
        {Edges.clear();}

    void clearHindrances()
        {Hindrances.clear();}

    QDomElement XmlSerialize(QDomDocument &doc) const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // EDGESANDHINDRANCES_H
