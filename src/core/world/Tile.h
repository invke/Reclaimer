//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TILE_H
#define RECLAIMER_TILE_H


struct Tile {
    int typeId;
    int x;
    int z;
    int y;

    Tile() : typeId(0), x(0), z(0), y(0) {}

    Tile(int typeId, int x, int z, int y)
            : typeId(typeId), x(x), z(z), y(y) {}

    bool operator=(Tile other) {
        typeId = other.typeId;
        x = other.x;
        z = other.z;
        y = other.y;
        return true;
    }
};


#endif //RECLAIMER_TILE_H