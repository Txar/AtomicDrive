#include <math.h>
#include "World.hpp"
#include "AtomicDrive/Math.cpp"

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
    sf::Vector2u res = r->getSize();
    int startX = ((float)camera.x/Tile::TILE_SIZE/Chunk::CHUNK_SIZE) - 2*Chunk::CHUNK_SIZE*Tile::TILE_SIZE;
    startX = std::max(startX, 0);

    int startY = ((float)camera.y/Tile::TILE_SIZE/Chunk::CHUNK_SIZE) - 2*Chunk::CHUNK_SIZE*Tile::TILE_SIZE;
    startY = std::max(startY, 0);

    int endX = (camera.x + (int)res.x)/Tile::TILE_SIZE/Chunk::CHUNK_SIZE + 2*Chunk::CHUNK_SIZE*Tile::TILE_SIZE;
    endX = std::min(endX, width);

    int endY = (camera.y + (int)res.y)/Tile::TILE_SIZE/Chunk::CHUNK_SIZE + 2*Chunk::CHUNK_SIZE*Tile::TILE_SIZE;
    endY = std::min(endY, height);

    //std::cout << startX << " " << endX << "\n";
    //startX = 0;
    //endX = width;
    //startY = 0;
    //endY = height;
    for (int i = startX; i < endX; i++) {
        for (int j = startY; j < endY; j++) {
            sf::Sprite s(chunkMap[i][j].drawBuffer.getTexture());
            s.setPosition(i*Tile::TILE_SIZE*Chunk::CHUNK_SIZE - camera.x, j*Tile::TILE_SIZE*Chunk::CHUNK_SIZE - camera.y);
            r->draw(s);
        }
    }
    //std::cout << g << std::endl;

    for (Entity &e : entities) {
        switch (e.renderer) {
            case (PLAYER): {

                break;
            }
            case (CAR): {
                sf::Sprite &s = e.sprite->sprite;
                //if (e.controller == PLAYER_CAR) s.setPosition(e.x - camera.x, e.y - camera.y);
                s.setPosition(e.x - camera.x, e.y - camera.y);
                //if (e.controller == AI_CAR) std::cout << e.x - camera.x << " " << e.y - camera.y << "\n";
                s.setOrigin(16.0, 24.0);
                s.setRotation(e.rotation);
                //if (e.x - camera.x > 0 && e.y - camera.y > 0) {
                r->draw(s);

                /*
                for (Collider &ec : e.colliders) {
                    //sf::Vector2i p = Math::iRotateAroundOrigin(ec.x, ec.y, e.rotation*Math::DEG_TO_RAD);
                    sf::Vector2i p = Math::iRotateAroundOrigin(ec.x + ec.width/2, ec.y + ec.height/2, e.rotation*Math::DEG_TO_RAD);
                    p.x += e.x - ec.width/2;
                    p.y += e.y - ec.height/2;
                    sf::RectangleShape rs({ec.width, ec.height});
                    rs.setPosition(p.x - camera.x, p.y - camera.y);
                    rs.setFillColor(sf::Color::Red);
                    r->draw(rs);
                }
                */
                //}
                
                break;
            }
            default:
                break;
        }
    }
}

void World::update() {

}