//
// Created by ptdave on 11/27/16.
//

#include "Inner.h"

#ifndef INNER_TILE_H
#define INNER_TILE_H

enum TileType {
    Solid = 0,
    Air = 1,
    Damaging = 2
};

class Tile : public sf::Sprite {
private:
    TileType tileType;
public:
    TileType getTileType() const {
        return tileType;
    }

    void setTileType(TileType tileType) {
        Tile::tileType = tileType;
    }

    virtual void update(const sf::Time &time) {

    }
};


#endif //INNER_TILE_H
