#ifndef EDGESANDHINDRANCES_H
#define EDGESANDHINDRANCES_H

#include <QVector>
#include "trait.h"

class EdgesAndHindrances
{
private:
    QVector<Trait> Edges{};
    QVector<Trait> Hindrances{};

public:
    EdgesAndHindrances();
};

#endif // EDGESANDHINDRANCES_H
