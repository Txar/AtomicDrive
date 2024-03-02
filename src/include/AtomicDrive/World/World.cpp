#include "World.hpp"

World::World() {

}

World::World(int width, int height) {
    this->width = width;
    this->height = height;

    chunkMap = new Chunk*[width];
    for (int i = 0; i < width; i++) {
        chunkMap[i] = new Chunk[height]();
    }
    //renderChunks();
}

void World::renderChunks() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            chunkMap[i][j].render();
        }
    }
}

void World::draw(sf::RenderTexture *r, sf::Vector2i &camera) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            sf::Sprite s(chunkMap[i][j].drawBuffer.getTexture());
            s.setPosition(i*Chunk::CHUNK_SIZE + camera.x, j*Chunk::CHUNK_SIZE + camera.y);
            r->draw(s);
        }
    }
}

void World::update() {

}