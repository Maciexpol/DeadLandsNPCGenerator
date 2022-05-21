#include "edgesandhindrances.h"

EdgesAndHindrances::EdgesAndHindrances()
{

}

qint16 EdgesAndHindrances::countBalance() const {
    qint16 edgesPoints{0};
    qint16 hindrancesPoints{0};

    for(auto trait : Edges){
        edgesPoints += trait.getPoints();
    }

    for(auto trait : Hindrances){
        hindrancesPoints+= trait.getPoints();
    }

    return hindrancesPoints - edgesPoints;

}
