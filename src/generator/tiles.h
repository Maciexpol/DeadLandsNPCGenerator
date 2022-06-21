#ifndef TILES_H
#define TILES_H

#include <QVector>
#include <random>
#include "attribute.h"

class Tiles
{
private:
    QVector<ATTRIBUTES> tiles{};

    void dropDown(qint16 index);

public:
    Tiles();
    Tiles(QVector<ATTRIBUTES> priority);
    Tiles(QVector<QString> priority);

    QVector<ATTRIBUTES> getTiles() const
        {return tiles;}

    void shuffleTiles(QVector<qint16> chances);
    void setTiles(QVector<ATTRIBUTES> priority);

    void moveTile(qint16 source, qint16 destination);

};

#endif // TILES_H

// we iterate from the right (the highest priority)
// every element has some chance for being dropped to the end
// this chance is increasing with every iteratation
//
// thanks to that if we drop something important at the end
// there is big chance for bubble it to the front
