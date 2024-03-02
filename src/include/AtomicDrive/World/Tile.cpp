#include "Tile.hpp"

void Tile::InitializeTypes() {

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