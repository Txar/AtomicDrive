#pragma once

class AtomicDrive;

#include "World/World.cpp"

class AtomicDrive {
    public:
        AtomicDrive();

        int mainLoop();
        void update();
        void draw();
        void pollEvents();

        Entity *player;
        sf::Vector2i camera;
        sf::RenderTexture terrainBuffer;
        sf::RenderWindow window;
        World world;
};