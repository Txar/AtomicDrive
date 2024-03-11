#pragma once

#include "SFML/Graphics.hpp"
#include "Tile.cpp"

class Chunk {
    public:
        static const int CHUNK_SIZE = 16;

        sf::RenderTexture drawBuffer;

        Tile **tiles;
        Chunk();

        bool loaded;

        Tile &at(int x, int y);
        void render();
        void unload();
};