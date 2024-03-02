#pragma once

#include "AtomicDrive/Graphics/TextureRect.cpp"

class Tile {
    public:
        Tile();
        Tile(bool solid, float durability, float friction, TextureRect *textureRect);
        Tile(bool solid, float durability, float friction, TextureRect &textureRect);
        void InitializeTypes();

        static const int TILE_SIZE = 16;
        static const Tile *types;

        bool isSolid;
        float durability;
        float health;
        float friction;
        TextureRect* textureRect;
        
        void update();
};