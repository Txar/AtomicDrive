#pragma once

#include "SFML/Graphics.hpp"
#include "Chunk.cpp"
#include "AtomicDrive/Entity/Entity.cpp"

class World {
    public:
        Chunk **chunkMap;
        std::vector<Entity> entities;
        int width, height;

        World();
        World(int width, int height);

        int targetX = 0, targetY = 0;

        void update();
        void renderChunks();
        void draw(sf::RenderTexture *r, sf::Vector2i &camera);

        Tile &at(int x, int y) {
            //std::cout << (int)floor(x / Chunk::CHUNK_SIZE) << " AA " << (int)floor(y / Chunk::CHUNK_SIZE) << std::endl;
            Chunk &c = chunkMap[(int)floor(x / Chunk::CHUNK_SIZE)][(int)floor(y / Chunk::CHUNK_SIZE)];
            return c.at(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE);
        }

        Tile &wAt(int x, int y) {
            return at(x / Tile::TILE_SIZE, y / Tile::TILE_SIZE);
        }

        Collider cAt(int x, int y) {
            Tile &t = at(x, y);
            if (t.isSolid) return Collider(
                x*Tile::TILE_SIZE, y*Tile::TILE_SIZE, 
                Tile::TILE_SIZE, Tile::TILE_SIZE);
            else return Collider();
        }
};