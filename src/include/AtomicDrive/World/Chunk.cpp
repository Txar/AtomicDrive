#include "Chunk.hpp"
#include <iostream>

Chunk::Chunk() {
    drawBuffer.create(Tile::TILE_SIZE*CHUNK_SIZE, Tile::TILE_SIZE*CHUNK_SIZE);
    drawBuffer.clear({0, 0, 0});
    
    Tile grass(false, 1.0, 1.0, TextureRect::types[TextureRect::GRASS]);

    tiles = new Tile*[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        tiles[i] = new Tile[CHUNK_SIZE]();
        for (int j = 0; j < CHUNK_SIZE; j++) {
            if ((rand()*100) % 99 == 1) tiles[i][j] = Tile(Tile::types[Tile::SAND_ROCK]);
            else tiles[i][j] = Tile(Tile::types[Tile::GRASS]);
            //tiles[i][j] = Tile(grass);
        }
    }
}

Tile &Chunk::at(int x, int y) {
    return tiles[x][y];
}

void Chunk::render() {
    drawBuffer.clear({0, 0, 0});
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            tiles[i][j].textureRect->sprite.setPosition(
                (float)Tile::TILE_SIZE*i, 
                (float)Tile::TILE_SIZE*j
            );
            drawBuffer.draw(tiles[i][j].textureRect->sprite);
        }
    }
    drawBuffer.display();
}

void Chunk::unload() {
    loaded = false;
    drawBuffer.~RenderTexture();
    delete &tiles;
}