#ifndef TILE_H
#define TILE_H

#include "attribute.h"

class Tile
{
private:
    ATTRIBUTES attribute;

public:
    Tile(ATTRIBUTES inputAttribute)
        {attribute = inputAttribute;}

};

#endif // TILE_H
