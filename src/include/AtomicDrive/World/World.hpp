#pragma once

#include "SFML/Graphics.hpp"
#include "Chunk.cpp"
#include "AtomicDrive/Entity/Entity.hpp"

class World {
    public:
        Chunk **chunkMap;
        std::vector<Entity> entities;
        int width, height;

        World();
        World(int width, int height);

        void update();
        void renderChunks();
        void draw(sf::RenderTexture *r, sf::Vector2i &camera);
};