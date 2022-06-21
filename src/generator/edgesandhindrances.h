#ifndef EDGESANDHINDRANCES_H
#define EDGESANDHINDRANCES_H

#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>
#include <random>
#include "trait.h"
#include "src/serializable.h"

class EdgesAndHindrances : Serializable
{
private:
    QVector<Trait> Edges{};
    QVector<Trait> Hindrances{};

    qint16 countPoints(const QVector<Trait> & traits) const;

public:
    EdgesAndHindrances();
    void rollEdgesAndHindrances();
    qint16 countBalance() const;

    qint8 getTraitsCount() const{return Edges.size() + Hindrances.size();}
    QVector<Trait> getEdges() const{return this->Edges;}
    QVector<Trait> getHindrances() const{return this->Hindrances;}

    void addEdge(const Trait & a)
        {Edges.push_back(a);}

    void addHindrance(const Trait & a)
        {Hindrances.push_back(a);}

    void clearEdges()
        {Edges.clear();}

    void clearHindrances()
        {Hindrances.clear();}

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;
};

#endif // EDGESANDHINDRANCES_H
