#ifndef EDGESANDHINDRANCES_H
#define EDGESANDHINDRANCES_H

#include <QVector>
#include "trait.h"

class EdgesAndHindrances
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

};

#endif // EDGESANDHINDRANCES_H
