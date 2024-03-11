#include "Tile.hpp"

Tile *Tile::types = new Tile[sizeof(Tile::TileTypes)]();

void Tile::initializeTypes() {
    types[GRASS] = Tile(false, 0, 1.0, TextureRect::types[TextureRect::GRASS]);
    types[SAND_ROCK] = Tile(true, 0, 1.0, TextureRect::types[TextureRect::SAND_ROCK]);
}

Tile::Tile() {}

Tile::Tile(bool solid, float durability, float friction, TextureRect *textureRect) {
    this->isSolid = solid;
    this->durability = durability;
    this->friction = friction;
    this->textureRect = textureRect;
}

Tile::Tile(bool solid, float durability, float friction, TextureRect &textureRect) {
    this->isSolid = solid;
    this->durability = durability;
    this->friction = friction;
    this->textureRect = &textureRect;
}