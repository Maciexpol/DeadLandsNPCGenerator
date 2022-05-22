#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "tiles.h"
#include "tileschances.h"
#include <QVector>


class TileManager
{
private:
    Tiles tiles{};

    TilesChances chances{};


public:
    TileManager();

    void shuffleTiles()
        {tiles.shuffleTiles(chances.getChances());}
};

#endif // TILEMANAGER_H
