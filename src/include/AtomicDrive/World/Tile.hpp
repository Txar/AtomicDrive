#pragma once

#include "AtomicDrive/Graphics/Button.hpp"

class Tile {
    public:
        Tile();
        Tile(bool solid, float durability, float friction, TextureRect *textureRect);
        Tile(bool solid, float durability, float friction, TextureRect &textureRect);

        enum TileTypes {
            GRASS,
            SAND,
            DIRT,
            SAND_ROCK,
            DIRT_ROCK
        };

        static Tile *types;
        static void initializeTypes();

        static const int TILE_SIZE = 16;

        bool isSolid;
        float durability;
        float health;
        float friction;
        TextureRect* textureRect;
        
        void update();
};