#pragma once

#include "World/World.cpp"

class AtomicDrive {
    public:
        AtomicDrive();

        int mainLoop();
        void update();
        void draw();
        void pollEvents();

        int fps;
        int frame;

        void drawUI();
        void AffectEntity(Entity &e, Effect effect);
        void calculateCarPhysics(Entity &e, float turning, sf::Vector2f acceleration, bool goingBack, World &world);
        Collider::CollisionType checkCarCollisions(Entity &e, World &world);
        
        Entity *player;
        sf::Vector2i camera;
        sf::RenderTexture worldBuffer;
        sf::Vector2i renderResolution;
        sf::RenderWindow window;
        SoundManager soundManager;
        World world;
};