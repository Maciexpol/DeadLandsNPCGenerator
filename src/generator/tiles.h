#ifndef TILES_H
#define TILES_H

#include <QVector>
#include "tile.h"

class Tiles
{
private:
    QVector<Tile> tiles{};

public:
    Tiles();
};

#endif // TILES_H

// we iterate from the right (the highest priority)
// every element has some chance for being dropped to the end
// this chance is increasing with every iteratation
//
// thanks to that if we drop something important at the end
// there is big chance for bubble it to the front
