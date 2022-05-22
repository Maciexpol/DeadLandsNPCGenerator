#ifndef TILESCHANCES_H
#define TILESCHANCES_H

#include <QVector>
#include <QtMath>

class TilesChances
{
private:
    QVector<qint16> chances{};
public:
    TilesChances();

    void linearChances(qint16 a, qint16 b = 0);
    void squareChances(qint16 a, qint16 b = 0, qint16 c = 0);
    void logChances(qint16 factor = 1);

    QVector<qint16> getChances() const
        {return chances;}

    void setChances(QVector<qint16> newChances)
        {chances = newChances;}
};

#endif // TILESCHANCES_H
