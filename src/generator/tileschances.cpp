#include "tileschances.h"

TilesChances::TilesChances()
{
    linearChances(5, -4);
}

void TilesChances::linearChances(qint16 a, qint16 b){
    chances.clear();

    for(qint16 i = 10; i > 0; i++){
        chances.append(a * i + b);
    }
}

void TilesChances::squareChances(qint16 a, qint16 b, qint16 c){
    chances.clear();

    for(qint16 i = 10; i > 0; i++){
        chances.append(a * i * i + b * i + c);
    }
}

void TilesChances::logChances(qint16 base){
    chances.clear();

    for(qint16 i = 10; i > 0; i++){
        chances.append(qLn(i) * base);
    }
}
